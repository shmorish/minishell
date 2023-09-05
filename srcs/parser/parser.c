/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/05 17:35:25 by morishitash      ###   ########.fr       */
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

void	evoluve_token(t_token *token_head)
{
	t_token	*tmp;
	char	*tmp_str;

	tmp = token_head->next;
	while (tmp != token_head && tmp->next != token_head)
	{
		if (can_connect_start(tmp) == true && can_connect(tmp->next) == true)
		{
			tmp_str = tmp->str;
			tmp->str = ft_strjoin(tmp_str, tmp->next->str);
			if (tmp->str == NULL)
			{
				ft_printf("\033[31m malloc error\n \033[0m");
				return ;
			}
			free(tmp_str);
			tmp->type = INCLUDE_QUOTE;
			token_node_delete(tmp->next);
		}
		else
			tmp = tmp->next;
	}
}

t_parser	*parser_node_new(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	new->input = NULL;
	new->output = NULL;
	return (new);
}

t_parser	*parser_init(void)
{
	t_parser	*head;

	head = parser_node_new();
	if (head == NULL)
		return (NULL);
	return (head);
}

void	free_parser_head_all(t_parser *head)
{
	t_parser	*tmp;
	t_input		*delete_input;
	t_output	*delete_output;
	t_parser	*delete;
	int			i;

	if (head == NULL)
		return ;
	tmp = head;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->cmd != NULL)
		{
			while (tmp->cmd[i] != NULL)
			{
				free(tmp->cmd[i]);
				i++;
			}
			free(tmp->cmd);
		}
		if (tmp->input != NULL)
		{
			while (tmp->input != NULL)
			{
				free(tmp->input->file_name);
				delete_input = tmp->input;
				tmp->input = tmp->input->next;
				free(delete_input);
			}
		}
		if (tmp->output != NULL)
		{
			while (tmp->output != NULL)
			{
				free(tmp->output->file_name);
				delete_output = tmp->output;
				tmp->output = tmp->output->next;
				free(delete_output);
			}
		}
		delete = tmp;
		tmp = tmp->next;
		free(delete);
	}
}

t_parser	*parser(t_token *token_head)
{
	t_parser	*parser_head;
	t_parser	*tmp;
	t_token		*tmp_token;
	t_output	*tmp_output;
	t_input		*tmp_input;
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
		ft_printf("tmp_token ; %s\n", tmp_token->str);
		if (tmp_token->str == NULL)
		{
			tmp_token = tmp_token->next;
			continue ;
		}
		if (tmp_token->type == PIPE)
		{
			tmp->next = parser_node_new();
			if (tmp->next == NULL)
			{
				free_parser_head_all(parser_head);
				return (NULL);
			}
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		else if (is_redirect(tmp_token) == true)
		{
			if (tmp_token->type == D_GREATER || tmp_token->type == S_GREATER)
			{
				if (tmp->output == NULL)
				{
					tmp->output = (t_output *)malloc(sizeof(t_output));
					if (tmp->output == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					tmp->output->next = NULL;
					tmp->output->file_name = ft_strdup(tmp_token->next->str);
					if (tmp->output->file_name == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					if (tmp_token->type == D_GREATER)
						tmp->output->type = APPEND;
					else
						tmp->output->type = OUT_FILE;
				}
				else
				{
					tmp_output = tmp->output;
					while (tmp_output->next != NULL)
						tmp_output = tmp_output->next;
					tmp_output->next = (t_output *)malloc(sizeof(t_output));
					if (tmp_output->next == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					tmp_output = tmp_output->next;
					tmp_output->next = NULL;
					tmp_output->file_name = ft_strdup(tmp_token->next->str);
					if (tmp_output->file_name == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					if (tmp_token->type == D_GREATER)
						tmp_output->type = APPEND;
					else
						tmp_output->type = OUT_FILE;
				}
			}
			else if (tmp_token->type == D_LESSER || tmp_token->type == S_LESSER)
			{
				if (tmp->input == NULL)
				{
					tmp->input = (t_input *)malloc(sizeof(t_input));
					if (tmp->input == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					tmp->input->next = NULL;
					tmp->input->file_name = ft_strdup(tmp_token->next->str);
					if (tmp->input->file_name == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					if (tmp_token->type == D_LESSER && tmp_token->next->type == INCLUDE_QUOTE)
						tmp->input->type = QUOTE_HEREDOC;
					else if (tmp_token->type == D_LESSER)
						tmp->input->type = HEREDOC;
					else
						tmp->input->type = IN_FILE;
				}
				else
				{
					tmp_input = tmp->input;
					while (tmp_input->next != NULL)
						tmp_input = tmp_input->next;
					tmp_input->next = (t_input *)malloc(sizeof(t_input));
					if (tmp_input->next == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					tmp_input = tmp_input->next;
					tmp_input->next = NULL;
					tmp_input->file_name = ft_strdup(tmp_token->next->str);
					if (tmp_input->file_name == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					if (tmp_token->type == D_LESSER && tmp_token->next->type == INCLUDE_QUOTE)
						tmp_input->type = QUOTE_HEREDOC;
					else if (tmp_token->type == D_LESSER)
						tmp_input->type = HEREDOC;
					else
						tmp_input->type = IN_FILE;
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
				{
					free_parser_head_all(parser_head);
					return (NULL);
				}
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
				{
					free_parser_head_all(parser_head);
					return (NULL);
				}
				i = 0;
				while (tmp->cmd[i] != NULL)
				{
					tmp_cmd[i] = ft_strdup(tmp->cmd[i]);
					if (tmp_cmd[i] == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					i++;
				}
				tmp_cmd[i] = ft_strdup(tmp_token->str);
				tmp_cmd[i + 1] = NULL;
				i = 0;
				while (tmp->cmd[i] != NULL)
				{
					free(tmp->cmd[i]);
					i++;
				}
				free(tmp->cmd);
				i = 0;
				while (tmp_cmd[i] != NULL)
					i++;
				tmp->cmd = (char **)malloc(sizeof(char *) * (i + 2));
				if (tmp->cmd == NULL)
				{
					free_parser_head_all(parser_head);
					return (NULL);
				}
				i = 0;
				while (tmp_cmd[i] != NULL)
				{
					tmp->cmd[i] = ft_strdup(tmp_cmd[i]);
					if (tmp->cmd[i] == NULL)
					{
						free_parser_head_all(parser_head);
						return (NULL);
					}
					i++;
				}
				tmp->cmd[i] = NULL;
				i = 0;
				while (tmp_cmd[i] != NULL)
				{
					free(tmp_cmd[i]);
					i++;
				}
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
