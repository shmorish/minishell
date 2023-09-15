/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/15 16:19:19 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	out_file(t_file *file, char *file_name)
{
	int	fd;

	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		g_signal = 1;
		return ;
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		g_signal = 1;
		return ;
	}
	if (file->next == NULL)
		dup2_error_exit(fd, STDOUT_FILENO);
	close_error_exit(fd);
}

void	append_file(t_file *file, char *file_name)
{
	int	fd;

	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		g_signal = 1;
		return ;
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		g_signal = 1;
		return ;
	}
	if (file->next == NULL)
		dup2_error_exit(fd, STDOUT_FILENO);
	close_error_exit(fd);
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
