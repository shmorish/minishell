/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipefd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:51:44 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/13 20:37:46 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	**make_pipefd(t_parser *parser_head)
{
	t_parser	*tmp;
	int			**pipefd;
	int			count;
	int			i;

	tmp = parser_head;
	count = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	pipefd = (int **)malloc(sizeof(int *) * (count + 1));
	if (pipefd == NULL)
		return (NULL);
	tmp = parser_head;
	i = 0;
	while (tmp->next != NULL)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipefd[i] == NULL)
			return (NULL); // need_free
		tmp = tmp->next;
		i++;
	}
	pipefd[i] = NULL;
	return (pipefd);
}
