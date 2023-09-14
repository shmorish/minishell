/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 02:44:11 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 03:01:24 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	next_pipe(t_pid *pid_data, int i)
{
	dup2_error_exit(pid_data->pipe_fd[i][1], STDOUT_FILENO);
	close_error_exit(pid_data->pipe_fd[i][0]);
	close_error_exit(pid_data->pipe_fd[i][1]);
}

void	prev_pipe(t_pid *pid_data, int i)
{
	dup2_error_exit(pid_data->pipe_fd[i - 1][0], STDIN_FILENO);
	close_error_exit(pid_data->pipe_fd[i - 1][0]);
	close_error_exit(pid_data->pipe_fd[i - 1][1]);
}

void	put_back_fd(t_pid *pid_data)
{
	dup2_error_exit(pid_data->stdin_fd, STDIN_FILENO);
	dup2_error_exit(pid_data->stdout_fd, STDOUT_FILENO);
	close_error_exit(pid_data->stdin_fd);
	close_error_exit(pid_data->stdout_fd);
}

void	parent_close_pipe(t_pid *pid_data, int i)
{
	close_error_exit(pid_data->pipe_fd[i - 1][0]);
	close_error_exit(pid_data->pipe_fd[i - 1][1]);
}

int	wait_error_exit(int *status)
{
	int	pid;

	pid = wait(status);
	if (pid == -1)
	{
		perror("wait");
		exit(1);
	}
	return (pid);
}
