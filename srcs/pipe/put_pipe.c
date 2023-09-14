/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 00:12:54 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/11 00:50:41 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_pipe(int **pipefd, int i)
{
	if (pipefd[0] == NULL)
		return ;
	if (i == 0)
	{
		dup2(pipefd[0][1], STDOUT_FILENO);
		close_pipefd(pipefd[0]);
	}
	else if (pipefd[i] == NULL)
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		close_pipefd(pipefd[i - 1]);
	}
	else
	{
		dup2(pipefd[i - 1][0], STDIN_FILENO);
		dup2(pipefd[i][1], STDOUT_FILENO);
		close_pipefd(pipefd[i - 1]);
		close_pipefd(pipefd[i]);
	}
}
