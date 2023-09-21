/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_pipe_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:49:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/21 13:46:36 by morishitash      ###   ########.fr       */
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
		signal_parent_init();
		if (wait_error_exit(&status) == pid_data->end_pid)
		{
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_status = WTERMSIG(status) + 128;
		}
		index++;
	}
}

void	child_process(t_pid *pid_data, int cmd_num,
	t_data *data, t_parser *tmp_parser)
{
	signal_child_init();
	if (tmp_parser->next != NULL)
		next_pipe(pid_data, cmd_num);
	if (tmp_parser->prev != NULL)
		prev_pipe(pid_data, cmd_num);
	// if (tmp_parser->input != NULL)
	// 	redirect_input(tmp_parser->input, data);
	// if (tmp_parser->output != NULL)
	// 	redirect_output(tmp_parser->output, data);
	if (g_signal != 1 && tmp_parser->cmd != NULL)
		select_commands(tmp_parser->cmd, data->env_head, data, CHILD);
	else if (g_signal != 1 && tmp_parser->cmd == NULL)
		data->exit_status = 0;
	close_error_exit(pid_data->stdin_fd);
	close_error_exit(pid_data->stdout_fd);
	exit(data->exit_status);
}

void	restore_child_and_fd(t_pid *pid_data, int cmd_num, t_data *data)
{
	wait_child(pid_data, cmd_num, data);
	put_back_fd(pid_data);
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
		{
			// pipe_error_exit(pid_data.pipe_fd[cmd_num]);
			if (pipe(pid_data.pipe_fd[cmd_num]) < 0)
			{
				perror("pipe");
				free_pipefd(pid_data.pipe_fd);
				put_back_fd(&pid_data);
				free(pid_data.pid);
				return (NULL);
			}
		}
		pid_data.pid[cmd_num] = fork_error_exit();
		if (pid_data.pid[cmd_num] == -1)
		{
			close_error_exit(pid_data.pipe_fd[cmd_num][0]);
			close_error_exit(pid_data.pipe_fd[cmd_num][1]);
			// free_pipefd(pid_data.pipe_fd);
			// free(pid_data.pid);
			// return (NULL);
			break ;
		}
		pid_data.end_pid = pid_data.pid[cmd_num];
		if (pid_data.pid[cmd_num] == 0)
			child_process(&pid_data, cmd_num, data, tmp_parser);
		tmp_parser = tmp_parser->next;
		if (cmd_num > 0)
			parent_close_pipe(&pid_data, cmd_num);
		cmd_num++;
	}
	restore_child_and_fd(&pid_data, cmd_num, data);
	free_pipefd(pid_data.pipe_fd);
	free(pid_data.pid);
	return ("OK");
}
