/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:29:28 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/20 17:05:28 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_files(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		free(file->file_name);
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

void	free_parser_head_all(t_parser *head)
{
	t_parser	*tmp;
	t_parser	*delete;
	int			i;

	if (head == NULL)
		return ;
	tmp = head;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->cmd != NULL)
		{
			while (tmp->cmd[i] != NULL)
				free(tmp->cmd[i++]);
			free(tmp->cmd);
		}
		if (tmp->file != NULL)
			free_files(tmp->file);
		delete = tmp;
		tmp = tmp->next;
		free(delete);
	}
	free(tmp);
}

void	*free_parser_null(t_parser *parser_head)
{
	free_parser_head_all(parser_head);
	return (NULL);
}
