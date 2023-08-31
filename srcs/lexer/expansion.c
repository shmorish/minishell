/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:42:53 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 17:57:47 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion(char *env_val, t_token *node, size_t start, size_t end)
{
	char	*before_str;
	char	*after_str;

	before_str = ft_substr(node->str, 0, start);
	if (before_str == NULL)
		return ;
	after_str = ft_substr(node->str, end, ft_strlen(node->str) - end);
	if (after_str == NULL)
	{
		free(before_str);
		return ;
	}
	expansion_join(node, before_str, after_str, env_val);
}

char	*expansion_get_env_val(char *env_name, t_env *env_head)
{
	char	*env_name_target;
	char	*env_val;

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

void	expansion_env(char *str, t_token *node, size_t *index, t_env *env_head)
{
	size_t	start;
	size_t	tmp_index;
	char	*env_name;
	char	*env_val;

	if (expansion_check_doll_end(str, index))
		return ;
	start = *index;
	while (ft_isalnum(str[*index]) || str[*index] == '_')
		(*index)++;
	if (str[*index] == '$')
	{
		tmp_index = *index;
		expansion_env(node->str, node, index, env_head);
		*index = tmp_index;
	}
	env_name = ft_substr(node->str, start, *index - start);
	if (env_name == NULL)
		return ;
	env_val = expansion_get_env_val(env_name, env_head);
	if (env_val == NULL)
		return ;
	expansion(env_val, node, --start, *index);
}

void	expansion_quote(t_token *node)
{
	char	*tmp;

	if (is_expansion(node->type))
	{
		if (node->type == D_QUOTE)
		{
			tmp = node->str;
			node->str = ft_strtrim(node->str, "\"");
			if (node->str == NULL)
				return ;
			free(tmp);
		}
		else if (node->type == S_QUOTE)
		{
			tmp = node->str;
			node->str = ft_strtrim(node->str, "\'");
			if (node->str == NULL)
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
		while (tmp_node->str[index])
		{
			if (tmp_node->str[index] == '$' && is_expansion(tmp_node->type))
			{
				expansion_env(tmp_node->str, tmp_node, &index, env_head);
			}
			index++;
		}
		expansion_quote(tmp_node);
		tmp_node = tmp_node->next;
	}
}
