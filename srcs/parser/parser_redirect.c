/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:37:21 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/08 17:56:11 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*file_init(t_file **file, char *file_mame,
	t_token_type type, t_token_type next_type)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		return (NULL);
	(*file)->next = NULL;
	(*file)->file_name = ft_strdup(file_mame);
	if ((*file)->file_name == NULL)
		return (NULL);
	if (type == D_LESSER && (next_type == INCLUDE_QUOTE
			|| next_type == D_QUOTE || next_type == S_QUOTE))
		(*file)->type = QUOTE_HEREDOC;
	else if (type == D_LESSER)
		(*file)->type = HEREDOC;
	else if (type == S_LESSER)
		(*file)->type = IN_FILE;
	else if (type == D_GREATER)
		(*file)->type = APPEND;
	else if (type == S_GREATER)
		(*file)->type = OUT_FILE;
	else
		(*file)->type = UNKNOWN;
	return (file);
}

static void	*add_files(t_file **file, char *file_name,
	t_token_type type, t_token_type next_type)
{
	t_file	*tmp_file;

	tmp_file = (*file);
	while (tmp_file->next != NULL)
		tmp_file = tmp_file->next;
	tmp_file->next = (t_file *)malloc(sizeof(t_file));
	if (tmp_file->next == NULL)
		return (NULL);
	tmp_file = tmp_file->next;
	tmp_file->next = NULL;
	tmp_file->file_name = ft_strdup(file_name);
	if (tmp_file->file_name == NULL)
		return (NULL);
	if (type == D_LESSER && (next_type == INCLUDE_QUOTE
			|| next_type == D_QUOTE || next_type == S_QUOTE))
		tmp_file->type = QUOTE_HEREDOC;
	else if (type == D_LESSER)
		tmp_file->type = HEREDOC;
	else if (type == S_LESSER)
		tmp_file->type = IN_FILE;
	else if (type == D_GREATER)
		tmp_file->type = APPEND;
	else if (type == S_GREATER)
		tmp_file->type = OUT_FILE;
	return (file);
}

static void	*parser_redirect_input(t_token **tmp_token, t_parser **tmp)
{
	if ((*tmp)->input == NULL)
	{
		if (file_init(&(*tmp)->input, (*tmp_token)->next->str,
				(*tmp_token)->type, (*tmp_token)->next->type) == NULL)
			return (NULL);
	}
	else
	{
		if (add_files(&(*tmp)->input, (*tmp_token)->next->str,
				(*tmp_token)->type, (*tmp_token)->next->type) == NULL)
			return (NULL);
	}
	return (tmp_token);
}

static void	*parser_redirect_output(t_token **tmp_token, t_parser **tmp)
{
	if ((*tmp)->output == NULL)
	{
		if (file_init(&(*tmp)->output, (*tmp_token)->next->str,
				(*tmp_token)->type, (*tmp_token)->next->type) == NULL)
			return (NULL);
	}
	else
	{
		if (add_files(&(*tmp)->output, (*tmp_token)->next->str,
				(*tmp_token)->type, (*tmp_token)->next->type) == NULL)
			return (NULL);
	}
	return (tmp_token);
}

void	*parser_redirect(t_token **tmp_token, t_parser **tmp)
{
	if ((*tmp_token)->type == D_GREATER || (*tmp_token)->type == S_GREATER)
	{
		if (parser_redirect_output(tmp_token, tmp) == NULL)
			return (NULL);
	}
	else if ((*tmp_token)->type == D_LESSER || (*tmp_token)->type == S_LESSER)
	{
		if (parser_redirect_input(tmp_token, tmp) == NULL)
			return (NULL);
	}
	(*tmp_token) = (*tmp_token)->next;
	return (tmp_token);
}
