/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:44:00 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/19 21:11:34 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	args_init(t_args **args_head)
// {
// 	*args_head = (t_args *)malloc(sizeof(t_args));
// 	if (*args_head == NULL)
// 	{
// 		ft_putendl_fd("malloc error", STDERR_FILENO);
// 		exit(1);
// 	}
// 	(*args_head)->args = NULL;
// 	(*args_head)->sign = NULL;
// 	(*args_head)->index = 0;
// 	(*args_head)->next = NULL;
// }

// t_args	*minishell_split(char *line)
// {
// 	t_args	*args_head;
// 	t_args	*args;
// 	size_t	i;
// 	size_t	index;

// 	args_head = NULL;
// 	args_init(&args_head);
// 	args = args_head;
// 	i = 0;
// 	index = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == ' ')
// 		{
// 			args->args = ft_split(line, ' ');
// 			args->index = index;
// 			args->next = (t_args *)malloc(sizeof(t_args));
// 			if (args->next == NULL)
// 			{
// 				ft_putendl_fd("malloc error", STDERR_FILENO);
// 				exit(1);
// 			}
// 			args = args->next;
// 			args_init(&args);
// 			index++;
// 		}
// 		else if (line[i] == '\'')
// 		{
			
// 		}
		
// 		i++;
// 	}
// }
