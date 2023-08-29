/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:42:53 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/29 12:42:28 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion(char *str, t_token *node, size_t start, size_t end, t_env *env_head)
{
	char	*tmp_env_name;
	char	*before_str;
	char	*after_str;
	char	*env_str;

	tmp_env_name = get_env_var(env_head, str);
	if (tmp_env_name == NULL)
		env_str = ft_strdup("");
	else
		env_str = ft_strdup(tmp_env_name);
	if (env_str == NULL)
		return ;
	before_str = ft_substr(node->data, 0, start);
	if (before_str == NULL)
		return ;
	after_str = ft_substr(node->data, end, ft_strlen(node->data) - end);
	if (after_str == NULL)
	{
		free(before_str);
		return ;
	}
	expansion_join(node, before_str, after_str, env_str);
}

void	expansion_env(char *data, t_token *node, size_t *index, t_env *env_head)
{
	size_t	start;
	size_t	tmp_index;
	char	*env_name;

	if (!count_doller(data, index))
		return ;
	if (data[*index] == '\0')
		return ;
	start = *index;
	while (ft_isalnum(data[*index]) || data[*index] == '_')
		(*index)++;
	if (data[*index] == '$')
	{
		tmp_index = *index;
		expansion_env(node->data, node, index, env_head);
		*index = tmp_index;
	}
	env_name = ft_substr(node->data, start, *index - start);
	if (env_name == NULL)
		return ;
	expansion(env_name, node, --start, *index, env_head);
	free(env_name);
}

void	expansion_quote(t_token *node)
{
	char	*tmp;

	if (is_expansion(node->type))
	{
		if (node->type == D_QUOTE)
		{
			tmp = node->data;
			node->data = ft_strtrim(node->data, "\"");
			if (node->data == NULL)
				return ;
			free(tmp);
		}
		else if (node->type == S_QUOTE)
		{
			tmp = node->data;
			node->data = ft_strtrim(node->data, "\'");
			if (node->data == NULL)
				return ;
			free(tmp);
		}
	}
}

void	expansion_check(t_token *token_head, t_env *env_head)
{
	t_token	*tmp_node;
	size_t	index;

	tmp_node = token_head->next;
	while (tmp_node != token_head)
	{
		index = 0;
		while (tmp_node->data[index])
		{
			if (tmp_node->data[index] == '$' && is_expansion(tmp_node->type))
			{
				expansion_env(tmp_node->data, tmp_node, &index, env_head);
			}
			index++;
		}
		expansion_quote(tmp_node);
		tmp_node = tmp_node->next;
	}
}
