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

int	g_signal = 0;

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
	data->exit_status = 0;
	return (data);
}

t_parser	*lexer_parser(t_data *data, char *line)
{
	t_parser	*parse_head;

	data->token_head = lexer(line, data);
	if (data->token_head == NULL)
	{
		free(line);
		return (NULL);
	}
	parse_head = parser(data->token_head);
	free_token_head_all(data->token_head);
	if (parse_head == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (parse_head);
}

void	main_exe(t_data *data, char *line)
{
	t_parser	*tmp_parser;

	tmp_parser = lexer_parser(data, line);
	if (tmp_parser == NULL)
		return ;
	if (tmp_parser->next == NULL)
		no_pipe_main(tmp_parser, data);
	else
		have_pipe_main(tmp_parser, data);
	free_parser_head_all(tmp_parser);
}

void	main_loop(t_data *data, char *line)
{
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
		main_exe(data, line);
		rm_heredoc_file();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*data;

	// print_ascii();
	data = data_init(argc, argv, envp);
	if (data == NULL)
		return (1);
	line = NULL;
	main_loop(data, line);
	return (0);
}
