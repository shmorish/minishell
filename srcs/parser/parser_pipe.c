/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:06:25 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/16 16:22:01 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*parser_pipe(t_parser **tmp, t_parser *parser_head)
{
	(*tmp)->next = parser_node_new();
	if ((*tmp)->next == NULL)
	{
		free_parser_head_all(parser_head);
		return (ft_puterr_malloc(), NULL);
	}
	(*tmp)->next->prev = *tmp;
	*tmp = (*tmp)->next;
	return (*tmp);
}
