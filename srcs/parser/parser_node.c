/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:44:55 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/16 16:21:51 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*parser_node_new(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (ft_puterr_malloc(), NULL);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	new->input = NULL;
	new->output = NULL;
	return (new);
}

t_parser	*parser_init(void)
{
	t_parser	*head;

	head = parser_node_new();
	if (head == NULL)
		return (ft_puterr_malloc(), NULL);
	return (head);
}
