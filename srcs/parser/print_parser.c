/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:08:03 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/06 16:07:26 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_parser_type(t_redirect_type type)
{
	if (type == QUOTE_HEREDOC)
		ft_printf("type = QUOTE_HEREDOC	:");
	else if (type == HEREDOC)
		ft_printf("type = HEREDOC	:");
	else if (type == IN_FILE)
		ft_printf("type = IN_FILE		:");
	else if (type == OUT_FILE)
		ft_printf("type = OUT_FILE		:");
	else if (type == APPEND)
		ft_printf("type = APPEND	:");
	else
		ft_printf("type = ERROR	:");
}

static void	print_parser_file(t_file *file)
{
	t_file	*file_tmp;

	file_tmp = file;
	while (file_tmp != NULL)
	{
		print_parser_type(file_tmp->type);
		ft_printf("%s\n", file_tmp->file_name);
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
		ft_printf("input\n");
		print_parser_file(parser_tmp->input);
		ft_printf("output\n");
		print_parser_file(parser_tmp->output);
		parser_tmp = parser_tmp->next;
		ft_printf("---------- pipe end ---------\n");
	}
}
