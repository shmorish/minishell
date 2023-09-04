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
	return (data);
}

void	free_line_newline(char *line, char *newline)
{
	free(line);
	free(newline);
}

t_token	*generate_token_example(void)
{
	t_token *example;

	example = (t_token *)malloc(sizeof(t_token));
	if (example == NULL)
		return (NULL);
	example->str = ft_strdup("aaa");
	example->type = STRING;
	example->next = (t_token *)malloc(sizeof(t_token));
	if (example->next == NULL)
		return (NULL);
	example->next->prev = example;
	example->next->str = ft_strdup("\"bbb\"");
	example->next->type = D_GREATER;
	example->next->next = (t_token *)malloc(sizeof(t_token));
	if (example->next->next == NULL)
		return (NULL);
	example->next->next->str = ft_strdup("ccc");
	example->next->next->type = STRING;
	example->next->next->next = NULL;
	example->next->next->prev = example->next;
	return (example);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char			*newline;
	char			**array;
	t_data			*data;
	t_parser		*parse_head;

	data = data_init(argc, argv, envp);
	if (data == NULL)
		return (1);
	signal_init();
	while (1)
	{
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
		newline = handle_quote(line, data->env_head, data);
		if (newline == NULL)
		{
			free(line);
			continue ;
		}
		if (ft_strlen(newline) == 0)
		{
			free(newline);
			continue ;
		}
		data->token_head = lexer(newline, data->env_head, data);
		if (data->exit_status == 258)
			continue ;
		// parse_head = parser(data->token_head);
		parse_head = parser(generate_token_example());
		(void)parse_head;
		array = ft_split(newline, ' ');
		if (array == NULL)
			break ;
		free_line_newline(line, newline);
		select_commands(array, data->env_head, data);
		free_char_array(array);
	}
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }