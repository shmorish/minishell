/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:00:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/21 11:28:42 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	fork_error_exit(void)
{
	int	ret;

	ret = fork();
	if (ret < 0)
	{
		perror("fork");
		// exit(1);
	}
	return (ret);
}

int	dup_error_exit(int oldfd)
{
	int	ret;

	ret = dup(oldfd);
	if (ret < 0)
	{
		// ft_printf("oldfd = %d\n", oldfd);
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

void	pipe_error_exit(int *pipefd)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret < 0)
	{
		perror("pipe");
	}
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
