/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:00:35 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/11 10:15:30 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_redirect(t_parser parser, t_data *data)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (parser->input != NULL)
		redirect_input(parser->input, data, NULL);
	if (parser->output != NULL)
		redirect_output(parser->output, data, NULL);
	if (parser->prev != NULL)
	{
		// connect pipe
	}
	if (parser->prev != NULL)
	{
		pipe_redirect(parser->prev, data);
	}
	select_commands(parser->cmd, data->env_head, data);
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
}
