/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/20 18:57:23 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	in_file(t_file *file, char *file_name, t_data *data, int *status)
{
	int	fd;

	(void)data;
	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		data->exit_status = 1;
		// g_signal = 1;
		*status = ERROR;
		return ;
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		print_errno(file_name);
		data->exit_status = 1;
		// g_signal = 1;
		*status = ERROR;
		return ;
	}
	if (file->next == NULL)
		dup2_error_exit(fd, STDIN_FILENO);
	close_error_exit(fd);
	data->exit_status = 0;
}

// void	redirect_input(t_file *file, t_data *data)
// {
// 	t_file	*tmp_file;

// 	tmp_file = file;
// 	while (tmp_file != NULL)
// 	{
// 		if (tmp_file->type == HEREDOC)
// 		{
// 			signal_heredoc();
// 			heredoc(tmp_file, tmp_file->file_name, data);
// 		}
// 		else if (tmp_file->type == QUOTE_HEREDOC)
// 		{
// 			signal_heredoc();
// 			quote_heredoc(tmp_file, tmp_file->file_name, data);
// 		}
// 		else if (tmp_file->type == IN_FILE)
// 			in_file(tmp_file, tmp_file->file_name, data);
// 		tmp_file = tmp_file->next;
// 	}
// }
