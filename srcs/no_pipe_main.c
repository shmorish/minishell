/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:40:22 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/20 16:19:42 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	no_pipe_main(t_parser *parser_head, t_data *data)
{
	int			stdin_fd;
	int			stdout_fd;
	t_parser	*tmp_parser;

	tmp_parser = parser_head;
	stdin_fd = dup_error_exit(STDIN_FILENO);
	stdout_fd = dup_error_exit(STDOUT_FILENO);
	if (tmp_parser->input != NULL)
		redirect_input(tmp_parser->input, data);
	if (tmp_parser->output != NULL)
		redirect_output(tmp_parser->output, data);
	if (g_signal != 1 && tmp_parser->cmd != NULL)
		select_commands(tmp_parser->cmd, data->env_head, data, PARENT);
	else if (g_signal != 1 && tmp_parser->cmd == NULL)
		data->exit_status = 0;
	dup2_error_exit(stdin_fd, STDIN_FILENO);
	dup2_error_exit(stdout_fd, STDOUT_FILENO);
	close_error_exit(stdin_fd);
	close_error_exit(stdout_fd);
}
