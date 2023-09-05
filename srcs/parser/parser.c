/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/05 18:54:02 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*parser(t_token *token_head)
{
	t_parser	*parser_head;
	t_parser	*tmp;
	t_token		*tmp_token;
	t_file		*tmp_file;
	int			i;
	char		**tmp_cmd;

	ft_printf("---------- parser start ---------\n");
	evoluve_token(token_head);
	parser_head = parser_init();
	if (parser_head == NULL)
		return (NULL);
	tmp = parser_head;
	tmp_token = token_head->next;
	i = 0;
	while (tmp_token != token_head)
	{
		if (tmp_token->str == NULL)
		{
			tmp_token = tmp_token->next;
			continue ;
		}
		if (tmp_token->type == PIPE)
		{
			tmp->next = parser_node_new();
			if (tmp->next == NULL)
				return (free_parser_null(parser_head));
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		else if (is_redirect(tmp_token) == true)
		{
			if (tmp_token->type == D_GREATER || tmp_token->type == S_GREATER)
			{
				if (tmp->output == NULL)
				{
					tmp->output = (t_file *)malloc(sizeof(t_file));
					if (tmp->output == NULL)
						return (free_parser_null(parser_head));
					tmp->output->next = NULL;
					tmp->output->file_name = ft_strdup(tmp_token->next->str);
					if (tmp->output->file_name == NULL)
						return (free_parser_null(parser_head));
					if (tmp_token->type == D_GREATER)
						tmp->output->type = APPEND;
					else
						tmp->output->type = OUT_FILE;
				}
				else
				{
					tmp_file = tmp->output;
					while (tmp_file->next != NULL)
						tmp_file = tmp_file->next;
					tmp_file->next = (t_file *)malloc(sizeof(t_file));
					if (tmp_file->next == NULL)
						return (free_parser_null(parser_head));
					tmp_file = tmp_file->next;
					tmp_file->next = NULL;
					tmp_file->file_name = ft_strdup(tmp_token->next->str);
					if (tmp_file->file_name == NULL)
						return (free_parser_null(parser_head));
					if (tmp_token->type == D_GREATER)
						tmp_file->type = APPEND;
					else
						tmp_file->type = OUT_FILE;
				}
			}
			else if (tmp_token->type == D_LESSER || tmp_token->type == S_LESSER)
			{
				if (tmp->input == NULL)
				{
					tmp->input = (t_file *)malloc(sizeof(t_file));
					if (tmp->input == NULL)
						return (free_parser_null(parser_head));
					tmp->input->next = NULL;
					tmp->input->file_name = ft_strdup(tmp_token->next->str);
					if (tmp->input->file_name == NULL)
						return (free_parser_null(parser_head));
					if (tmp_token->type == D_LESSER && tmp_token->next->type == INCLUDE_QUOTE)
						tmp->input->type = QUOTE_HEREDOC;
					else if (tmp_token->type == D_LESSER)
						tmp->input->type = HEREDOC;
					else
						tmp->input->type = IN_FILE;
				}
				else
				{
					tmp_file = tmp->input;
					while (tmp_file->next != NULL)
						tmp_file = tmp_file->next;
					tmp_file->next = (t_file *)malloc(sizeof(t_file));
					if (tmp_file->next == NULL)
						return (free_parser_null(parser_head));
					tmp_file = tmp_file->next;
					tmp_file->next = NULL;
					tmp_file->file_name = ft_strdup(tmp_token->next->str);
					if (tmp_file->file_name == NULL)
						return (free_parser_null(parser_head));
					if (tmp_token->type == D_LESSER && tmp_token->next->type == INCLUDE_QUOTE)
						tmp_file->type = QUOTE_HEREDOC;
					else if (tmp_token->type == D_LESSER)
						tmp_file->type = HEREDOC;
					else
						tmp_file->type = IN_FILE;
				}
			}
			tmp_token = tmp_token->next;
		}
		else
		{
			if (tmp->cmd == NULL)
			{
				tmp->cmd = (char **)malloc(sizeof(char *) * 2);
				if (tmp->cmd == NULL)
					return (free_parser_null(parser_head));
				tmp->cmd[0] = ft_strdup(tmp_token->str);
				tmp->cmd[1] = NULL;
			}
			else
			{
				i = 0;
				while (tmp->cmd[i] != NULL)
					i++;
				tmp_cmd = (char **)malloc(sizeof(char *) * (i + 2));
				if (tmp_cmd == NULL)
					return (free_parser_null(parser_head));
				i = 0;
				while (tmp->cmd[i] != NULL)
				{
					tmp_cmd[i] = ft_strdup(tmp->cmd[i]);
					if (tmp_cmd[i] == NULL)
						return (free_parser_null(parser_head));
					i++;
				}
				tmp_cmd[i] = ft_strdup(tmp_token->str);
				tmp_cmd[i + 1] = NULL;
				i = 0;
				while (tmp->cmd[i] != NULL)
					free(tmp->cmd[i++]);
				free(tmp->cmd);
				i = 0;
				while (tmp_cmd[i] != NULL)
					i++;
				tmp->cmd = (char **)malloc(sizeof(char *) * (i + 2));
				if (tmp->cmd == NULL)
					return (free_parser_null(parser_head));
				i = 0;
				while (tmp_cmd[i] != NULL)
				{
					tmp->cmd[i] = ft_strdup(tmp_cmd[i]);
					if (tmp->cmd[i] == NULL)
						return (free_parser_null(parser_head));
					i++;
				}
				tmp->cmd[i] = NULL;
				i = 0;
				while (tmp_cmd[i] != NULL)
					free(tmp_cmd[i++]);
				free(tmp_cmd);
			}
		}
		tmp_token = tmp_token->next;
	}
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	parser_head = tmp;
	ft_printf("---------- parser result ---------\n");
	ft_printf("---------- parser result end ---------\n");
	free_parser_head_all(parser_head);
	return (parser_head);
}
