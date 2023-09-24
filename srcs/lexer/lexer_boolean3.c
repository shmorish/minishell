/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_boolean3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:08:36 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/24 10:14:32 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	lexer_token_main(char *line, size_t *index, t_token *head, t_data *data)
{
	if (lexer_token(line, index, head))
	{
		(*index)++;
		return (true);
	}
	else
	{
		data->exit_status = 258;
		free_token_head_all(head);
		return (false);
	}
}

bool	is_left_space(t_token_type type)
{
	if (type == LSP_D_QUOTE || type == LSP_S_QUOTE
		|| type == L_SPACE_STR)
		return (true);
	else
		return (false);
}

bool	is_no_space(t_token_type type)
{
	if (type == STRING || type == S_QUOTE
		|| type == D_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_heredoc_expansion(t_token *node)
{
	if (node->prev->type == D_LESSER)
		return (true);
	else if (is_left_space(node->prev->type)
		&& node->prev->prev->type == D_LESSER)
		return (true);
	else if (is_no_space(node->prev->type))
		return (is_heredoc_expansion(node->prev));
	else
		return (false);
}

bool	is_env_name(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}
