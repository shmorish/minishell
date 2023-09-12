/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_boolean2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:19:27 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/11 11:04:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_only_space_before(char *line, size_t index)
{
	if (index == 0)
		return (true);
	index--;
	while (index && line[index] == ' ')
		index--;
	if (index == 0)
		return (true);
	else
		return (false);
}

bool	is_only_space_or_end(char *line, size_t index)
{
	while (line[index] && line[index] == ' ')
		index++;
	if (line[index] == '\0')
		return (true);
	else
		return (false);
}

bool	is_valid_greater(char *line, size_t index)
{
	if (line[index] == '>')
		index++;
	else if (line[index] == '<')
	{
		ft_puterr("minishell: syntax error near unexpected token `<'\n");
		return (false);
	}
	if (line[index] == '>')
	{
		ft_puterr("minishell: syntax error near unexpected token `>'\n");
		return (false);
	}
	else
		return (true);
}

bool	is_valid_lesser(char *line, size_t index)
{
	if (line[index] == '<')
		index++;
	else if (line[index] == '>')
	{
		ft_puterr(ERR_NEWLINE);
		return (false);
	}
	if (line[index] == '<')
	{
		ft_puterr(ERR_NEWLINE);
		return (false);
	}
	else
		return (true);
}
