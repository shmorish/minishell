/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:29:28 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/03 02:13:27 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_parser_block(char	**block)
{
	int	i;

	i = 0;
	while (block[i] != NULL)
	{
		free(block[i]);
		i++;
	}
	free(block);
}

void	free_parser(t_parser *parser_head)
{
	while (parser_head != NULL)
	{
		free_parser_block(parser_head->cmd);
		parser_head = parser_head->next;
		free(parser_head->prev);
	}
}
