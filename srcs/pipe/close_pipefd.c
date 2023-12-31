/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipefd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:55:41 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/11 00:55:31 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipefd(int pipefd[2])
{
	if (pipefd[0] != -1)
		close(pipefd[0]);
	if (pipefd[1] != -1)
		close(pipefd[1]);
}

void	close_last_pipefd(int **pipefd)
{
	int	i;

	i = 0;
	if (pipefd == NULL)
		return ;
	if (pipefd[0] == NULL)
		return ;
	while (pipefd[i] != NULL)
		i++;
	close_pipefd(pipefd[i - 1]);
}
