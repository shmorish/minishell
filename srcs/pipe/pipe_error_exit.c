/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:00:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/22 12:55:09 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_error(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
	{
		perror("fork");
	}
	return (ret);
}

int	dup_error_exit(int oldfd)
{
	int	ret;

	ret = dup(oldfd);
	if (ret < 0)
	{
		perror("dup");
		exit(1);
	}
	return (ret);
}

int	dup2_error_exit(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret < 0)
	{
		perror("dup2");
		exit(1);
	}
	return (ret);
}

int	pipe_error(int *pipefd)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret < 0)
	{
		perror("pipe");
	}
	return (ret);
}

int	close_error_exit(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret < 0)
	{
		perror("close");
		exit(1);
	}
	return (ret);
}
