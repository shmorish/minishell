/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 12:45:11 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	in_file(t_file *file, char *file_name, t_data *data)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr_nofile(file_name);
		data->exit_status = 1;
		return ;
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

void	redirect_input(t_file *file, t_data *data)
{
	t_file	*tmp_file;

	tmp_file = file;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == HEREDOC)
		{
			signal_heredoc();
			heredoc(tmp_file, tmp_file->file_name, data);
		}
		else if (tmp_file->type == QUOTE_HEREDOC)
		{
			signal_heredoc();
			quote_heredoc(tmp_file, tmp_file->file_name, data);
		}
		else if (tmp_file->type == IN_FILE)
			in_file(tmp_file, tmp_file->file_name, data);
		tmp_file = tmp_file->next;
	}
}
