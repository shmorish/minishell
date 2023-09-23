/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:07:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/23 13:46:51 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	red_in_fd(t_file *file, char *file_name,
		t_data *data, int *status)
{
	if (file->type == IN_FILE)
		return (in_file(file, file_name, data, status));
	else if (file->type == HEREDOC)
	{
		signal_heredoc();
		return (heredoc(file, file_name, data));
	}
	else if (file->type == QUOTE_HEREDOC)
	{
		signal_heredoc();
		return (quote_heredoc(file, file_name, data));
	}
	else
		return (0);
}

static int	red_out_fd(t_file *file, char *file_name,
		t_data *data, int *status)
{
	if (file->type == OUT_FILE)
		return (out_file(file, file_name, data, status));
	else if (file->type == APPEND)
		return (append(file, file_name, data, status));
	else
		return (0);
}

static void	dup2_redirect(int tmp_in_fd, int tmp_out_fd, t_data *data,
		int *status)
{
	if (tmp_in_fd != -1)
	{
		dup2_error_exit(tmp_in_fd, STDIN_FILENO);
		close_error_exit(tmp_in_fd);
	}
	if (tmp_out_fd != -1)
	{
		dup2_error_exit(tmp_out_fd, STDOUT_FILENO);
		close_error_exit(tmp_out_fd);
	}
	if (*status == ERROR)
		data->exit_status = 1;
}

void	redirect(t_parser *parser, t_data *data, int *status)
{
	t_file	*file;
	int		tmp_in_fd;
	int		tmp_out_fd;

	file = parser->file;
	tmp_in_fd = -1;
	tmp_out_fd = -1;
	while (file != NULL && *status != ERROR)
	{
		if (is_input_redirect(file->type) == true)
		{
			if (tmp_in_fd != -1)
				close_error_exit(tmp_in_fd);
			tmp_in_fd = red_in_fd(file, file->file_name, data, status);
		}
		else if (is_output_redirect(file->type) == true)
		{
			if (tmp_out_fd != -1)
				close_error_exit(tmp_out_fd);
			tmp_out_fd = red_out_fd(file, file->file_name, data, status);
		}
		file = file->next;
	}
	dup2_redirect(tmp_in_fd, tmp_out_fd, data, status);
}
