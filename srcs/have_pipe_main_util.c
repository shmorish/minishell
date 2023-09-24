/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_pipe_main_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmorish <shmorish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:03:06 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/24 11:03:58 by shmorish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*pid_init(t_pid *pid_data, t_parser *parser_head)
{
	pid_data->pid = count_process(parser_head);
	if (pid_data->pid == NULL)
		return (NULL);
	pid_data->end_pid = 0;
	pid_data->stdin_fd = dup_error_exit(STDIN_FILENO);
	pid_data->stdout_fd = dup_error_exit(STDOUT_FILENO);
	pid_data->pipe_fd = make_pipefd(parser_head);
	if (pid_data->pipe_fd == NULL)
	{
		free(pid_data->pid);
		return (NULL);
	}
	return ("OK");
}
