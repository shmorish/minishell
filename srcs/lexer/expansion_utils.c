/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:27:24 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/29 13:26:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_expansion(t_token_type type)
{
	if (type == D_QUOTE || type == S_QUOTE || type == STRING || type == R_SPACE_STR)
		return (true);
	else
		return (false);
}

bool	is_str_token(t_token_type type)
{
	if (type == STRING || type == R_SPACE_STR || type == L_SPACE_STR)
		return (true);
	else
		return (false);
}

void	expansion_free(char *before_str, char *after_str, char *env_str)
{
	free(before_str);
	free(after_str);
	free(env_str);
}

void	expansion_join(t_token *node, char *before, char *after, char *env_str)
{
	char	*tmp_data;

	tmp_data = node->data;
	node->data = ft_strjoin(before, env_str);
	free(tmp_data);
	if (node->data == NULL)
	{
		expansion_free(before, after, env_str);
		return ;
	}
	tmp_data = node->data;
	node->data = ft_strjoin(tmp_data, after);
	free(tmp_data);
	if (node->data == NULL)
	{
		expansion_free(before, after, env_str);
		return ;
	}
	expansion_free(before, after, env_str);
}

bool	count_doller(char *data, size_t *index)
{
	size_t	count_dollar;

	count_dollar = 0;
	while (data[*index] == '$')
	{
		(*index)++;
		count_dollar++;
	}
	if (count_dollar % 2 == 0)
		return (false);
	else
		return (true);
}
