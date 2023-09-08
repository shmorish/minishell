/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:42:00 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/05 18:38:56 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	can_connect_start(t_token *token_head)
{
	if (token_head->type == LSP_S_QUOTE || token_head->type == LSP_D_QUOTE
		|| token_head->type == S_QUOTE || token_head->type == D_QUOTE
		|| token_head->type == COMMAND || token_head->type == FILE_OR_DIR
		|| token_head->type == STRING || token_head->type == INCLUDE_QUOTE
		|| token_head->type == R_SPACE_STR || token_head->type == L_SPACE_STR)
		return (true);
	return (false);
}

bool	can_connect(t_token *token_head)
{
	if (token_head->type == S_QUOTE || token_head->type == D_QUOTE
		|| token_head->type == COMMAND || token_head->type == FILE_OR_DIR
		|| token_head->type == STRING || token_head->type == INCLUDE_QUOTE
		|| token_head->type == R_SPACE_STR)
		return (true);
	return (false);
}

bool	is_connectable_quote(t_token *token_head)
{
	if (token_head->type == S_QUOTE || token_head->type == D_QUOTE
		|| token_head->type == INCLUDE_QUOTE)
		return (true);
	return (false);
}

bool	is_redirect(t_token *token_head)
{
	if (token_head->type == S_GREATER || token_head->type == D_GREATER
		|| token_head->type == S_LESSER || token_head->type == D_LESSER)
		return (true);
	return (false);
}
