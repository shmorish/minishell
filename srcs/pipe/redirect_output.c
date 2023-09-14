/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 11:58:58 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	out_file(t_file *file, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (file->next == NULL)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	append_file(t_file *file, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (file->next == NULL)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	redirect_output(t_file *file, t_data *data)
{
	t_file	*tmp_file;

	(void)data;
	tmp_file = file;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == OUT_FILE)
			out_file(tmp_file, tmp_file->file_name);
		else if (tmp_file->type == APPEND)
			append_file(tmp_file, tmp_file->file_name);
		tmp_file = tmp_file->next;
	}
}
