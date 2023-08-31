/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/31 11:24:37 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_parser
{
	char			**block;
	t_token_type	type;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parser;

// COMMAND, PIPE, S_GREATER, D_GREATER, S_LESSER, D_LESSER, FILE_OR_DIR

// typedef enum e_parse_type
// {
// 	PIPE,
// 	COMMAND,
// 	ARG,
// 	FILE,
// 	S_GREATER, // >
// 	D_GREATER, // >>
// 	S_LESSER, // <
// 	D_LESSER, // <<
// }	t_parse_type;

// parser_node_new
// parser_node_add_back

t_parser	*parser_node_new(char *data, t_token_type type)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		return (NULL);
	new->block = data;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	parser_node_add_back(t_parser **head, t_parser *new)
{
	t_parser	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
}


t_parser	*parser(t_token *token_head)
{
	t_parser	*parse_head;
	char		*tmp;

	parse_head = NULL;
	while (token_head != NULL)
	{
		if (token_head->type == PIPE)
		{
			tmp = ft_strdup("|");
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, PIPE));
			free(tmp);
		}
		else if (token_head->type == S_GREATER)
		{
			tmp = ft_strdup(">");
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, S_GREATER));
			free(tmp);
		}
		else if (token_head->type == D_GREATER)
		{
			tmp = ft_strdup(">>");
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, D_GREATER));
			free(tmp);
		}
		else if (token_head->type == S_LESSER)
		{
			tmp = ft_strdup("<");
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, S_LESSER));
			free(tmp);
		}
		else if (token_head->type == D_LESSER)
		{
			tmp = ft_strdup("<<");
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, D_LESSER));
			free(tmp);
		}
		else if (token_head->type == STRING)
		{
			tmp = ft_strdup(token_head->data);
			if (tmp == NULL)
				return (NULL);
			parser_node_add_back(&parse_head, parser_node_new(tmp, STRING));
			free(tmp);
		}
	}
}
