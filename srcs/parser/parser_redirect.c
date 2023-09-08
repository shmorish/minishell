/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 20:37:21 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/06 19:00:49 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*file_init(t_file **file, char *file_mame)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		return (NULL);
	(*file)->next = NULL;
	(*file)->file_name = ft_strdup(file_mame);
	if ((*file)->file_name == NULL)
		return (NULL);
	return (file);
}

static void	*add_files(t_file **file, char *file_name)
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
	return (file);
}

static void	*parser_redirect_input(t_token **tmp_token, t_parser **tmp)
{
	if ((*tmp)->input == NULL)
	{
		if (file_init(&(*tmp)->input, (*tmp_token)->next->str) == NULL)
			return (NULL);
	}
	else
	{
		if (add_files(&(*tmp)->input, (*tmp_token)->next->str) == NULL)
			return (NULL);
	}
	if ((*tmp_token)->type == D_LESSER
		&& (*tmp_token)->next->type == INCLUDE_QUOTE)
		(*tmp)->input->type = QUOTE_HEREDOC;
	else if ((*tmp_token)->type == D_LESSER)
		(*tmp)->input->type = HEREDOC;
	else if ((*tmp_token)->type == S_LESSER)
		(*tmp)->input->type = IN_FILE;
	else
		(*tmp)->input->type = UNKNOWN;
	return (tmp_token);
}

static void	*parser_redirect_output(t_token **tmp_token, t_parser **tmp)
{
	if ((*tmp)->output == NULL)
	{
		if (file_init(&(*tmp)->output, (*tmp_token)->next->str) == NULL)
			return (NULL);
	}
	else
	{
		if (add_files(&(*tmp)->output, (*tmp_token)->next->str) == NULL)
			return (NULL);
	}
	if ((*tmp_token)->type == D_GREATER)
		(*tmp)->output->type = APPEND;
	else if ((*tmp_token)->type == S_GREATER)
		(*tmp)->output->type = OUT_FILE;
	else
		(*tmp)->output->type = UNKNOWN;
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
