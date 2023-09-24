/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:05:50 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/22 12:09:33 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef enum e_redirect_type	t_redirect_type;

bool	is_input_redirect(t_redirect_type type)
{
	if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
		return (true);
	return (false);
}

bool	is_output_redirect(t_redirect_type type)
{
	if (type == OUT_FILE || type == APPEND)
		return (true);
	return (false);
}
