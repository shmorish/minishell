/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/03 19:13:13 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// parser_node_new
// parser_node_add_back

// t_parser	*parser_node_new(char *data, t_redirect_type type)
// {
// 	t_parser	*new;

// 	new = (t_parser *)malloc(sizeof(t_parser));
// 	if (new == NULL)
// 		return (NULL);
// 	new->cmd = ft_strdup(data);
// 	new->type = type;
// 	new->next = NULL;
// 	new->prev = NULL;
// 	return (new);
// }

// t_parser	put_redirect_to_node(t_parser *parser_head, t_token *token_head)
// {
// 	t_parser		*new;
// 	t_token			*tmp;
// 	t_redirect_type	type;

// 	tmp = token_head;
// 	if (tmp->type == S_GREATER)
// 		type = OUT_FILE;
// 	else if (tmp->type == D_GREATER)
// 		type = APPEND;
// 	else if (tmp->type == S_LESSER)
// 		type = IN_FILE;
// 	else if (tmp->type == D_LESSER)
// 	{
// 		if (token_head->next->type == INCLUDE_QUOTE)
// 			type = QUOTE_HEREDOC;
// 		else
// 			type = HEREDOC;
// 	}
// 	new = parser_node_new(tmp->data, type);
// 	if (new == NULL)
// 		return (NULL);
// 	if (parser_head == NULL)
// 	{
// 		parser_head = new;
// 		return (parser_head);
// 	}
// 	while (parser_head->next != NULL)
// 		parser_head = parser_head->next;
// 	parser_head->next = new;
// 	new->prev = parser_head;
// 	while (parser_head->prev != NULL)
// 		parser_head = parser_head->prev;
// 	return (parser_head);
// }

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

t_token	*evoluve_token(t_token	*token_head)
{
	t_token	*new;
	t_token	*tmp;
	char	*str;

	if (token_head == NULL)
		return (NULL);
	// new = (t_token *)malloc(sizeof(t_token));
	// if (new == NULL)
	// 	return (NULL);
	new = NULL;
	// ft_printf("token_head->str : %s\n", token_head->str);
	// ft_printf("token_head->type: %d\n", token_head->type);
	// ft_printf("evoluve_token\n");
	while (token_head != NULL)
	{
		tmp = (t_token *)malloc(sizeof(t_token));
		if (tmp == NULL)
			return (NULL); // free_all
		if (new == NULL)
		{
			new = tmp;
			new->prev = NULL;
		}
		else
		{
			new->next = tmp;
			tmp->prev = new;
			new = new->next;
		}
		if (token_head->next != NULL && can_connect_start(token_head) == true)
		{
			if (can_connect(token_head->next) == true)
			{
				str = ft_strjoin(token_head->str, token_head->next->str);
				new->str = str;
				if (is_connectable_quote(token_head) == true)
					new->type = INCLUDE_QUOTE;
				else
					new->type = STRING;
				token_head = token_head->next->next;
			}
			else
			{
				new->type = token_head->type;
				new->str = ft_strdup(token_head->str);
				token_head = token_head->next;
			}
		}
		else
		{
			new->type = token_head->type;
			new->str = ft_strdup(token_head->str);
			token_head = token_head->next;
		}
	}
	while (new->prev != NULL)
		new = new->prev;
	return (new);
}

t_parser	*parser(t_token *token_head)
{
	// t_parser	*parse_head;
	t_token		*new_token;
	// char		*tmp;

	// parse_head = NULL;
	ft_printf("---------- parser start ---------\n");
	new_token = evoluve_token(token_head);
	if (new_token == NULL)
		return (NULL);
	ft_printf("---------- finish evoluve_token ---------\n");
	while (new_token != NULL)
	{
		printf("type:	%d\n", new_token->type);
		printf("str:	%s\n", new_token->str);
		new_token = new_token->next;
	}
	ft_printf("--------------------\n");
	// while (token_head != NULL)
	// {
	// 	if (new_token->type == S_GREATER || new_token->type == D_GREATER
	// 		|| new_token->type == S_LESSER || new_token->type == D_LESSER)
	// 	{
	// 		parse_head = put_redirect_to_node(parse_head, new_token);
	// 		new_token = new_token->next;
	// 		if (new_token->next == NULL) // 来ることなさそう。
	// 		{
	// 			ft_putendl_fd("syntax error near unexpected token `newline'", 2);
	// 			return (NULL);
	// 		}
	// 		new_token = new_token->next;
	// 	}
	// }
	return (NULL);
}
