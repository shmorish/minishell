/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bool2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:52:54 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/16 12:54:11 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_string(t_token_type type)
{
	if (type == STRING || type == L_SPACE_STR || type == R_SPACE_STR)
		return (true);
	return (false);
}
