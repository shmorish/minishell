/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/10 13:16:31 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_output(t_file *file_head, t_data *data, int pipefd[2])
{
	t_file	*file_tmp;
	int		fd;

	(void)data;
	file_tmp = file_head;
	while (file_tmp != NULL)
	{
		if (file_tmp->type == OUT_FILE)
		{
			fd = open(file_tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(fd);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		else if (file_tmp->type == APPEND)
		{
			fd = open(file_tmp->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("open");
				exit(1);
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				exit(1);
			}
			close(fd);
			close(pipefd[0]);
			close(pipefd[1]);
		}
	}
}
