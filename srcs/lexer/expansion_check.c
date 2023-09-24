/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:22:28 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/24 10:14:45 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*expansion_last(t_token *tmp_node)
{
	expansion_quote(tmp_node);
	if (tmp_node->type == DELETE)
		tmp_node = expansion_split(tmp_node);
	if (tmp_node == NULL)
		return (ft_puterr_malloc(), NULL);
	return (tmp_node);
}

void	expansion_main(t_token *tmp_node, t_data *data)
{
	size_t	index;

	index = 0;
	while (tmp_node->str[index])
	{
		if (tmp_node->str[index] == '$' && is_expansion(tmp_node->type))
		{
			if (!is_env_name(tmp_node->str[index + 1])
				&& tmp_node->str[index + 1] != '$'
				&& tmp_node->str[index + 1] != '?')
				index++;
			else if (!is_heredoc_expansion(tmp_node))
			{
				if (expansion_env(tmp_node->str, tmp_node, &index, data))
					index = 0;
			}
			else
				break ;
		}
		else
			index++;
	}
}

void	expansion_check(t_token *token_head, t_data *data)
{
	t_token	*tmp_node;

	tmp_node = token_head->next;
	while (tmp_node != token_head)
	{
		if (is_expansion(tmp_node->type))
			expansion_main(tmp_node, data);
		tmp_node = expansion_last(tmp_node);
		tmp_node = tmp_node->next;
	}
}
