/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:42:53 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 16:14:37 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expansion(char *str, t_token *node, size_t start, size_t end, t_env *env_head)
{
	char	*tmp_env_name;
	char	*before_str;
	char	*after_str;
	char	*env_str;

	tmp_env_name = get_env_val(env_head, str);
	if (tmp_env_name == NULL)
		env_str = ft_strdup("");
	else
		env_str = ft_strdup(tmp_env_name);
	if (env_str == NULL)
		return ;
	before_str = ft_substr(node->str, 0, start);
	if (before_str == NULL)
		return ;
	after_str = ft_substr(node->str, end, ft_strlen(node->str) - end);
	if (after_str == NULL)
	{
		free(before_str);
		return ;
	}
	expansion_join(node, before_str, after_str, env_str);
}

void	expansion_env(char *str, t_token *node, size_t *index, t_env *env_head)
{
	size_t	start;
	size_t	tmp_index;
	char	*env_name;

	if (!count_doller(str, index))
		return ;
	if (str[*index] == '\0')
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
