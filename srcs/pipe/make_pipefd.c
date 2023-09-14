/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipefd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 00:51:44 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/14 11:55:56 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_parser(t_parser *parser_head)
{
	t_parser	*tmp;
	int			count;

	tmp = parser_head;
	count = 0;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

static void	*free_pipefd_null(int **pipefd)
{
	int	i;

	i = 0;
	while (pipefd[i] != NULL)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
	return (NULL);
}

int	**make_pipefd(t_parser *parser_head)
{
	t_parser	*tmp;
	int			**pipefd;
	int			count;
	int			i;

	count = count_parser(parser_head);
	pipefd = (int **)malloc(sizeof(int *) * (count + 1));
	if (pipefd == NULL)
		return (NULL);
	tmp = parser_head;
	i = 0;
	while (tmp->next != NULL)
	{
		pipefd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipefd[i] == NULL)
			return (free_pipefd_null(pipefd));
		tmp = tmp->next;
		i++;
	}
	pipefd[i] = NULL;
	return (pipefd);
}
