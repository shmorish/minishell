/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:29:28 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/05 18:38:07 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_input(t_file *input)
{
	t_file	*tmp;

	while (input != NULL)
	{
		free(input->file_name);
		tmp = input;
		input = input->next;
		free(tmp);
	}
}

static void	free_output(t_file *output)
{
	t_file	*tmp;

	while (output != NULL)
	{
		free(output->file_name);
		tmp = output;
		output = output->next;
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
		if (tmp->input != NULL)
			free_input(tmp->input);
		if (tmp->output != NULL)
			free_output(tmp->output);
		delete = tmp;
		tmp = tmp->next;
		free(delete);
	}
}
