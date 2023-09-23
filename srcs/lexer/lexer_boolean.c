/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_boolean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:40:31 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/23 16:47:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_token(char c)
{
	if (c == '\'' || c == '\"' || c == '>' || c == '<' || c == '|')
		return (true);
	else
		return (false);
}

bool	is_expansion(t_token_type type)
{
	if (type == D_QUOTE || type == STRING || type == L_SPACE_STR
		|| type == R_SPACE_STR || type == LSP_D_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_str_token(t_token_type type)
{
	if (type == STRING || type == R_SPACE_STR || type == L_SPACE_STR)
		return (true);
	else
		return (false);
}

bool	is_quote(t_token_type type)
{
	if (type == D_QUOTE || type == S_QUOTE || type == LSP_D_QUOTE
		|| type == LSP_S_QUOTE || type == INCLUDE_QUOTE)
		return (true);
	else
		return (false);
}

bool	is_dredirect_pipe(t_token_type type)
{
	if (type == D_LESSER || type == D_LESSER || type == PIPE)
		return (true);
	else
		return (false);
}
