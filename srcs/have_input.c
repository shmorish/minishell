/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:20:18 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/26 13:27:15 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	input_exsist(t_parser *parser)
{
	t_parser	*tmp_parser;

	tmp_parser = parser;
	while (tmp_parser != NULL)
	{
		if (tmp_parser->file != NULL)
		{
			if (tmp_parser->file->type == IN_FILE)
				return (true);
			else if (tmp_parser->file->type == HEREDOC)
				return (true);
			else if (tmp_parser->file->type == QUOTE_HEREDOC)
				return (true);
		}
		tmp_parser = tmp_parser->next;
	}
	return (false);
}

void	have_input(t_parser *parser, t_pid *pid_data)
{
	t_parser	*tmp_parser;

	tmp_parser = parser;
	if (input_exsist(tmp_parser) == true)
	{
		dup2_error_exit(pid_data->stdin_fd, STDIN_FILENO);
	}
}
