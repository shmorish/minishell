/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_boolean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:40:31 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/29 14:51:10 by ryhara           ###   ########.fr       */
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
		ft_puterr("minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	if (line[index] == '<')
	{
		ft_puterr("minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	else
		return (true);
}
