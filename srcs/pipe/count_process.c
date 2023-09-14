/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 02:18:47 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 01:55:22 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	*count_process(t_parser *parser_head)
{
	t_parser	*tmp;
	pid_t		*pid;
	int			count;

	tmp = parser_head;
	count = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	pid = (pid_t *)malloc(sizeof(pid_t) * (count + 1));
	if (pid == NULL)
		return (NULL);
	return (pid);
}
