/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:08:03 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/05 20:16:55 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_parser_file(t_file *file)
{
	t_file	*file_tmp;

	file_tmp = file;
	while (file_tmp != NULL)
	{
		ft_printf("file_name = %s\n", file_tmp->file_name);
		file_tmp = file_tmp->next;
	}
}

void	print_parser(t_parser *parser_head)
{
	t_parser	*parser_tmp;
	int			i;

	parser_tmp = parser_head;
	while (parser_tmp != NULL)
	{
		ft_printf("---------- pipe result ---------\n");
		i = 0;
		if (parser_tmp->cmd != NULL)
		{
			while (parser_tmp->cmd[i] != NULL)
			{
				ft_printf("cmd[%d] = %s\n", i, parser_tmp->cmd[i]);
				i++;
			}
		}
		print_parser_file(parser_tmp->input);
		print_parser_file(parser_tmp->output);
		parser_tmp = parser_tmp->next;
		ft_printf("---------- pipe end ---------\n");
	}
}
