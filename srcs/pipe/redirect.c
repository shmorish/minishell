/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:07:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/20 18:56:14 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect(t_parser *parser, t_data *data)
{
	t_file	*file;
	int		status;

	status = NORMAL;
	file = parser->file;
	while (file != NULL)
	{
		if (file->type == HEREDOC)
		{
			signal_heredoc();
			heredoc(file, file->file_name, data);
		}
		else if (file->type == QUOTE_HEREDOC)
		{
			signal_heredoc();
			quote_heredoc(file, file->file_name, data);
		}
		file = file->next;
	}
	file = parser->file;
	while (file != NULL)
	{
		if (status == ERROR)
			break ;
		if (file->type == IN_FILE)
			in_file(file, file->file_name, data, &status);
		else if (file->type == OUT_FILE)
			out_file(file, file->file_name, data, &status);
		else if (file->type == APPEND)
			append(file, file->file_name, data, &status);
		file = file->next;
	}
}
