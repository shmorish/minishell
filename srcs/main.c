/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:59:23 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 15:59:23 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal = 0;

t_data	*data_init(int argc, char **argv, char **envp)
{
	t_data	*data;
	t_env	*env_head;

	(void)argc;
	(void)argv;
	env_head = env_init(envp);
	if (env_head == NULL)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->env_head = env_head;
	data->envp = envp;
	data->exit_status = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			**pipe_fd;
	pid_t		pid;
	t_data		*data;
	t_parser	*parse_head;
	t_parser	*tmp_parser;
	int			i;
	int			stdin_fd;
	int			stdout_fd;

	data = data_init(argc, argv, envp);
	if (data == NULL)
		return (1);
	while (1)
	{
		signal_main_init();
		line = readline("\033[1;34mminishell \033[0m $> ");
		if (line == NULL)
		{
			free_env_head_all(data->env_head);
			free(line);
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		data->token_head = lexer(line, data);
		if (data->token_head == NULL)
		{
			free(line);
			continue ;
		}
		parse_head = parser(data->token_head);
		free_token_head_all(data->token_head);
		if (parse_head == NULL)
		{
			free(line);
			continue ;
		}
		free(line);
		pipe_fd = make_pipefd(parse_head);
		if (pipe_fd == NULL)
		{
			free_parser_head_all(parse_head);
			continue ;
		}
		tmp_parser = parse_head;
		i = 0;
		if (tmp_parser != NULL)
		{
			stdin_fd = dup(STDIN_FILENO);
			stdout_fd = dup(STDOUT_FILENO);
			// if (tmp_parser->input->type == HEREDOC)
			// {
			// 	ft_printf("<<\n");

			// }
			if (tmp_parser->input != NULL)
				redirect_input(tmp_parser->input, data, pipe_fd[i]);
			if (tmp_parser->output != NULL)
				redirect_output(tmp_parser->output, data, pipe_fd[i]);
			select_commands(tmp_parser->cmd, data->env_head, data);
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
			tmp_parser = tmp_parser->next;
			i++;
		}
		while (tmp_parser != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				stdin_fd = dup(STDIN_FILENO);
				stdout_fd = dup(STDOUT_FILENO);
				if (tmp_parser->input != NULL)
					redirect_input(tmp_parser->input, data, pipe_fd[i]);
				if (tmp_parser->output != NULL)
					redirect_output(tmp_parser->output, data, pipe_fd[i]);
				close_pipefd(pipe_fd[i]);
				select_commands(tmp_parser->cmd, data->env_head, data);
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
				exit(data->exit_status);
			}
			else if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			else
			{
				waitpid(pid, &data->exit_status, 0);
				close_pipefd(pipe_fd[i]);
			}
			tmp_parser = tmp_parser->next;
			i++;
		}
		free_pipefd(pipe_fd);
		free_parser_head_all(parse_head);
		rm_heredoc_file();
	}
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }