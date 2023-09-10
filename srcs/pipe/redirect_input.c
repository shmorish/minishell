/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/10 13:16:23 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(char *file_name, int pipefd[2])
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	quote_heredoc(char *file_name, int pipefd[2])
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	in_file(char *file_name, int pipefd[2])
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	redirect_input(t_file *file, t_data *data, int pipefd[2])
{
	(void)data;
	if (file->type == HEREDOC)
		heredoc(file->file_name, pipefd);
	else if (file->type == QUOTE_HEREDOC)
		quote_heredoc(file->file_name, pipefd);
	else if (file->type == IN_FILE)
		in_file(file->file_name, pipefd);
}
