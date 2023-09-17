/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:40:22 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/17 12:40:46 by ryhara           ###   ########.fr       */
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
	dup2_error_exit(stdin_fd, STDIN_FILENO);
	dup2_error_exit(stdout_fd, STDOUT_FILENO);
}
