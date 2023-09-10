/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/10 17:25:11 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(char *file_name)
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
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	quote_heredoc(char *file_name)
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
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	in_file(char *file_name)
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
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	redirect_input(t_file *file, t_data *data, int pipefd[2])
{
	(void)data;
	(void)pipefd;
	if (file->type == HEREDOC)
		heredoc(file->file_name);
	else if (file->type == QUOTE_HEREDOC)
		quote_heredoc(file->file_name);
	else if (file->type == IN_FILE)
		in_file(file->file_name);
}
