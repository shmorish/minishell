/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:21:10 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/04 20:19:26 by ryhara           ###   ########.fr       */
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

void	evoluve_token(t_token	*token_head)
{
	t_token	*tmp;
	// t_token	*new_token;
	char	*tmp_str;
	t_token *a;
	tmp = token_head->next;
	while (tmp != token_head && tmp->next != token_head)
	{
		if (can_connect_start(tmp) == true && can_connect(tmp->next) == true)
		{
			// new_token = (t_token *)malloc(sizeof(t_token));
			// if (new_token == NULL)
			// {
			// 	free_token_head_all(token_head);
			// 	return ;
			// }
			tmp_str = tmp->str;
			tmp->str = ft_strjoin(tmp_str, tmp->next->str);
			if (tmp->str == NULL)
			{
				ft_printf("@@@@@@@@@@@@@@@@@@@@@@ malloc erro r@@@@@@@@@@@@@@@@@@@@@@-\n");
				return ;
			}
			free(tmp_str);
			tmp->type = INCLUDE_QUOTE;
			token_node_delete(tmp->next);
			// new_token->prev = tmp->prev;
			// new_token->next = tmp->next->next;
			// tmp->prev->next = new_token;
			// tmp->next->next->prev = new_token;
			// free(tmp->next->str);
			// free(tmp->str);
			// free(tmp->next);
			// free(tmp);
			// tmp = new_token;

			printf("------------------");
			a = token_head->next;
			while (a != token_head)
			{
				printf("tmp %s tmp->next %s\n", a->str, a->next->str);
				a = a->next;
			}
		}
		else
			tmp = tmp->next;
	}
}

// t_parser	*parser_node_new(char *str)
// {
// 	t_token	*new;

// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (new == NULL)
// 		return (NULL);
// 	if (ft_strlen(str) == 0)
// 		new->str = NULL;
// 	else
// 	{
// 		new->str = ft_strdup(str);
// 		if (new->str == NULL)
// 			return (NULL);
// 	}
// 	set_token_type(new);
// 	new->next = NULL;
// 	new->prev = NULL;
// 	return (new);
// }

// t_parser	*parser_init(t_parser *parser_head)
// {
// 	t_token	*head;

// 	head = token_node_new("");
// 	if (head == NULL)
// 		return (NULL);
// 	head->next = head;
// 	head->prev = head;
// 	return (head);
// }

t_parser	*parser(t_token *token_head)
{
	// t_parser	*parser_head;
	// t_token		*new_token;
	t_token		*tmp;
	// t_parser	*tmp;

	ft_printf("---------- parser start ---------\n");
	evoluve_token(token_head);
	ft_printf("------ finish evoluve_token ------\n");
	tmp = token_head->next;
	while (tmp != token_head)
	{
		printf("type:	%d\n", tmp->type);
		printf("str:	%s\n", tmp->str);
		tmp = tmp->next;
	}
	ft_printf("--------------------\n");
	// tmp = parser_init(parser_head);
	return (NULL);
}
