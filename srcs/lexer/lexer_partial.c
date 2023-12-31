/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_partial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:42:21 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/11 11:03:33 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	lexer_single_quote(char *line, size_t *index)
{
	while (line[*index])
	{
		(*index)++;
		if (line[*index] == '\'')
			return (true);
	}
	ft_puterr(ERR_QUOTE);
	return (false);
}

bool	lexer_double_quote(char *line, size_t *index)
{
	while (line[*index])
	{
		(*index)++;
		if (line[*index] == '\"')
			return (true);
	}
	ft_puterr(ERR_QUOTE);
	return (false);
}

bool	lexer_pipe(char *line, size_t *index)
{
	if (is_only_space_before(line, *index))
	{
		ft_puterr(ERR_PIPE);
		return (false);
	}
	else if (is_only_space_or_end(line, *index + 1))
	{
		ft_puterr(ERR_PIPE);
		return (false);
	}
	else
	{
		if (line[*index + 1] == '|')
		{
			ft_puterr(ERR_PIPE);
			return (false);
		}
		else
			return (true);
	}
}

bool	lexer_greater(char *line, size_t *index)
{
	if (is_only_space_or_end(line, *index + 1))
	{
		ft_puterr(ERR_NEWLINE);
		return (false);
	}
	else if (is_valid_greater(line, *index + 1))
	{
		if (line[*index + 1] == '>')
			(*index)++;
		if (is_only_space_or_end(line, *index + 1))
		{
			ft_puterr(ERR_NEWLINE);
			return (false);
		}
		return (true);
	}
	else
		return (false);
}

bool	lexer_lesser(char *line, size_t *index)
{
	if (is_only_space_or_end(line, *index + 1))
	{
		ft_puterr(ERR_NEWLINE);
		return (false);
	}
	else if (is_valid_lesser(line, *index + 1))
	{
		if (line[*index + 1] == '<')
			(*index)++;
		if (is_only_space_or_end(line, *index + 1))
		{
			ft_puterr(ERR_NEWLINE);
			return (false);
		}
		return (true);
	}
	else
		return (false);
}
