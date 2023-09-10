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
	// int			**pipe_fd;
	// int			pid;
	t_data		*data;
	t_parser	*parse_head;
	t_parser	*tmp_parser;

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
		// pipe_fd = make_pipefd(parse_head);
		tmp_parser = parse_head;
		while (tmp_parser != NULL)
		{
			// pid = fork();
			select_commands(tmp_parser->cmd, data->env_head, data);
			tmp_parser = tmp_parser->next;
		}
		free_parser_head_all(parse_head);
	}
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }