/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_evolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:43:33 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/16 16:19:59 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	evoluve_token(t_token *token_head)
{
	t_token	*tmp;
	char	*tmp_str;

	tmp = token_head->next;
	while (tmp != token_head && tmp->next != token_head)
	{
		if (can_connect_start(tmp) == true && can_connect(tmp->next) == true)
		{
			tmp_str = tmp->str;
			tmp->str = ft_strjoin(tmp_str, tmp->next->str);
			if (tmp->str == NULL)
				return (ft_puterr_malloc());
			free(tmp_str);
			tmp->type = INCLUDE_QUOTE;
			token_node_delete(tmp->next);
		}
		else
			tmp = tmp->next;
	}
}
