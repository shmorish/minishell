/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:08:44 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 16:08:51 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_enum_utils(t_token *node)
{
	if (node->type == COMMAND)
		ft_printf(" %s\n", "COMMAND");
	else if (node->type == FILE_OR_DIR)
		ft_printf(" %s\n", "FILE_OR_DIR");
	else if (node->type == STRING)
		ft_printf(" %s\n", "STRING");
	else if (node->type == R_SPACE_STR)
		ft_printf(" %s\n", "R_SPACE_STR");
	else if (node->type == L_SPACE_STR)
		ft_printf(" %s\n", "L_SPACE_STR");
	else if (node->type == SEMICOLON)
		ft_printf(" %s\n", "SEMICOLON");
}

void	print_enum(t_token *node)
{
	if (node->type == EMPTY)
		ft_printf(" %s\n", "EMPTY");
	else if (node->type == PIPE)
		ft_printf(" %s\n", "PIPE");
	else if (node->type == S_QUOTE)
		ft_printf(" %s\n", "S_QUOTE");
	else if (node->type == D_QUOTE)
		ft_printf(" %s\n", "D_QUOTE");
	else if (node->type == S_GREATER)
		ft_printf(" %s\n", "S_GREATER");
	else if (node->type == D_GREATER)
		ft_printf(" %s\n", "D_GREATER");
	else if (node->type == S_LESSER)
		ft_printf(" %s\n", "S_LESSER");
	else if (node->type == D_LESSER)
		ft_printf(" %s\n", "D_LESSER");
	else
		print_enum_utils(node);
}

void	print_lexer(t_token *token_head)
{
	t_token	*tmp;

	tmp = token_head->next;
	while (tmp != token_head)
	{
		ft_printf("%s:", tmp->str);
		print_enum(tmp);
		tmp = tmp->next;
	}
}
