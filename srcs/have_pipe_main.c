/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_pipe_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:49:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 03:24:05 by morishitash      ###   ########.fr       */
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

void	wait_child(t_pid *pid_data, int cmd_num, t_data *data)
{
	int	index;
	int	status;

	index = 0;
	while (index < cmd_num)
	{
		if (wait_error_exit(&status) == pid_data->end_pid)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_status = WTERMSIG(status);
		}
		index++;
	}
}

void	child_process(t_pid *pid_data, int cmd_num,
	t_data *data, t_parser *tmp_parser)
{
	if (tmp_parser->next != NULL)
		next_pipe(pid_data, cmd_num);
	if (tmp_parser->prev != NULL)
		prev_pipe(pid_data, cmd_num);
	if (tmp_parser->input != NULL)
		redirect_input(tmp_parser->input, data);
	if (tmp_parser->output != NULL)
		redirect_output(tmp_parser->output, data);
	select_commands(tmp_parser->cmd, data->env_head, data);
	exit(data->exit_status);
}

void	restore_child_and_fd(t_pid *pid_data, int cmd_num, t_data *data)
{
	wait_child(&pid_data, cmd_num, data);
	put_back_fd(&pid_data);
}

void	*have_pipe_main(t_parser *parser_head, t_data *data)
{
	t_pid		pid_data;
	t_parser	*tmp_parser;
	int			cmd_num;

	cmd_num = 0;
	if (pid_init(&pid_data, parser_head) == NULL)
		return (NULL);
	tmp_parser = parser_head;
	while (tmp_parser != NULL)
	{
		if (tmp_parser->next != NULL)
			pipe_error_exit(pid_data.pipe_fd[cmd_num]);
		pid_data.pid[cmd_num] = fork_error_exit();
		pid_data.end_pid = pid_data.pid[cmd_num];
		if (pid_data.pid[cmd_num] == 0)
			child_process(&pid_data, cmd_num, data, tmp_parser);
		tmp_parser = tmp_parser->next;
		if (cmd_num > 0)
			parent_close_pipe(&pid_data, cmd_num);
		cmd_num++;
	}
	restore_child_and_fd(&pid_data, cmd_num, data)
	free_pipefd(pid_data.pipe_fd);
	free(pid_data.pid);
	return ("OK");
}
