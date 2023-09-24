/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:40:22 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/22 11:15:25 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_pipe_main(t_parser *parser_head, t_data *data)
{
	int			stdin_fd;
	int			stdout_fd;
	t_parser	*tmp_parser;
	int			redirect_status;

	redirect_status = NORMAL;
	tmp_parser = parser_head;
	stdin_fd = dup_error_exit(STDIN_FILENO);
	stdout_fd = dup_error_exit(STDOUT_FILENO);
	if (tmp_parser->file != NULL)
		redirect(tmp_parser, data, &redirect_status);
	if (g_signal != 1 && tmp_parser->cmd != NULL && redirect_status == NORMAL)
		select_commands(tmp_parser->cmd, data->env_head, data, PARENT);
	else if (g_signal != 1 && tmp_parser->cmd == NULL
		&& redirect_status == NORMAL)
		data->exit_status = 0;
	dup2_error_exit(stdin_fd, STDIN_FILENO);
	dup2_error_exit(stdout_fd, STDOUT_FILENO);
	close_error_exit(stdin_fd);
	close_error_exit(stdout_fd);
}
