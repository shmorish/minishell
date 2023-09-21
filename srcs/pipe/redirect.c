/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:07:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/21 18:55:28 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect(t_parser *parser, t_data *data)
{
	t_file	*file;
	int		status;
	int		tmp_in_fd;
	int		tmp_out_fd;

	status = NORMAL;
	file = parser->file;
	tmp_in_fd = -1;
	tmp_out_fd = -1;
	while (file != NULL)
	{
		if (status == ERROR)
			break ;
		if (file->type == IN_FILE)
		{
			if (tmp_in_fd != -1)
				close(tmp_in_fd);
			tmp_in_fd = in_file(file, file->file_name, data, &status);
		}
		else if (file->type == HEREDOC)
		{
			if (tmp_in_fd != -1)
				close(tmp_in_fd);
			signal_heredoc();
			tmp_in_fd = heredoc(file, file->file_name, data);
		}
		else if (file->type == QUOTE_HEREDOC)
		{
			if (tmp_in_fd != -1)
				close(tmp_in_fd);
			signal_heredoc();
			tmp_in_fd = quote_heredoc(file, file->file_name, data);
		}
		else if (file->type == OUT_FILE)
		{
			if (tmp_out_fd != -1)
				close(tmp_out_fd);
			tmp_out_fd = out_file(file, file->file_name, data, &status);
		}
		else if (file->type == APPEND)
		{
			if (tmp_out_fd != -1)
				close(tmp_out_fd);
			tmp_out_fd = append(file, file->file_name, data, &status);
		}
		file = file->next;
	}
	if (tmp_in_fd != -1)
		dup2_error_exit(tmp_in_fd, STDIN_FILENO);
	if (tmp_out_fd != -1)
		dup2_error_exit(tmp_out_fd, STDOUT_FILENO);
}
