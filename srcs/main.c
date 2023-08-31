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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*newline;
	char		**array;
	t_env		*env_head;
	t_data		*data;
	t_token		*token_head;

	(void)argc;
	(void)argv;
	env_head = env_init(envp);
	if (env_head == NULL)
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	data->env_head = env_head;
	data->envp = envp;
	signal_init();
	while (1)
	{
		line = readline("\033[1;34mminishell \033[0m $> ");
		if (line == NULL)
		{
			free_env_head_all(env_head);
			free(line);
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		newline = handle_quote(line, env_head, data);
		if (newline == NULL)
		{
			free(line);
			continue ;
		}
		token_head = lexer(newline, env_head);
		(void)token_head;
		// list = ft_split_quote(newline, ' ');
		array = ft_split(newline, ' ');
		if (array == NULL)
			break ;
		free(line);
		free(newline);
		select_commands(array, env_head, data);
		free_char_array(array);
	}
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }