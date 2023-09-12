/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/12 13:02:28 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	in_file(t_file *file, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (file->next == NULL)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
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

void	redirect_input(t_file *file, t_data *data, int pipefd[2])
{
	t_file	*tmp_file;

	(void)data;
	(void)pipefd;
	tmp_file = file;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == HEREDOC)
			heredoc(tmp_file, tmp_file->file_name, data);
		else if (tmp_file->type == QUOTE_HEREDOC)
			quote_heredoc(tmp_file, tmp_file->file_name, data);
		else if (tmp_file->type == IN_FILE)
			in_file(tmp_file, tmp_file->file_name);
		tmp_file = tmp_file->next;
	}
}
