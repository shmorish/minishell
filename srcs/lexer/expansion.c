/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:42:53 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/18 12:07:06 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion(char *env_val, t_token *node, size_t start, size_t end)
{
	char	*before_str;
	char	*after_str;

	before_str = ft_substr(node->str, 0, start);
	if (before_str == NULL)
		return (ft_puterr_malloc());
	after_str = ft_substr(node->str, end, ft_strlen(node->str) - end);
	if (after_str == NULL)
	{
		free(before_str);
		return (ft_puterr_malloc());
	}
	expansion_join(node, before_str, after_str, env_val);
}

char	*expansion_get_env_val(char *env_name, t_env *env_head, t_data *data)
{
	char	*env_name_target;
	char	*env_val;

	if (!ft_strcmp(env_name, "?"))
	{
		env_val = ft_itoa(data->exit_status);
		free(env_name);
		if (env_val == NULL)
			return (NULL);
		else
			return (env_val);
	}
	(void)data;
	env_name_target = get_env_val(env_head, env_name);
	free(env_name);
	if (env_name_target == NULL)
		env_val = ft_strdup("");
	else
		env_val = ft_strdup(env_name_target);
	if (env_val == NULL)
		return (NULL);
	return (env_val);
}

bool	expansion_env(char *str, t_token *node, size_t *index, t_data *data)
{
	size_t	start;
	size_t	tmp_index;
	char	*env_name;
	char	*env_val;

	if (expansion_check_doll_end(str, index))
		return (false);
	start = *index;
	while (ft_isalnum(str[*index]) || str[*index] == '_')
		(*index)++;
	if (str[*index] == '?')
		(*index)++;
	if (str[*index] == '$')
	{
		tmp_index = *index;
		expansion_env(node->str, node, index, data);
		*index = tmp_index;
	}
	env_name = ft_substr(node->str, start, *index - start);
	if (env_name == NULL)
		return (ft_puterr_malloc(), false);
	env_val = expansion_get_env_val(env_name, data->env_head, data);
	if (env_val == NULL)
		return (ft_puterr_malloc(), false);
	return (expansion(env_val, node, --start, *index), true);
}

void	expansion_quote(t_token *node)
{
	char	*tmp;

	if (is_expansion(node->type) || node->type == S_QUOTE
		|| node->type == LSP_S_QUOTE)
	{
		if (node->type == D_QUOTE || node->type == LSP_D_QUOTE)
		{
			tmp = node->str;
			node->str = ft_strtrim(tmp, "\"");
			if (node->str == NULL)
				return (ft_puterr_malloc());
			free(tmp);
		}
		else if (node->type == S_QUOTE || node->type == LSP_S_QUOTE)
		{
			tmp = node->str;
			node->str = ft_strtrim(tmp, "\'");
			if (node->str == NULL)
				return (ft_puterr_malloc());
			free(tmp);
		}
	}
}

t_token	*expansion_split(t_token *node)
{
	char	**array;
	t_token	*delete_node;
	size_t	i;

	delete_node = node;
	i = 0;
	array = ft_split_charset(node->str, " \t");
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
	{
		token_node_insert(node, token_node_new(array[i]));
		node = node->next;
		node->type = L_SPACE_STR;
		i++;
	}
	token_node_delete(delete_node);
	free_char_array(array);
	return (node);
}
