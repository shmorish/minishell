/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:24:16 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/17 12:14:52 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_node_new(char *str)
{
	t_token	*new;

	if (str == NULL)
		return (NULL);
	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
		new->str = NULL;
	else
	{
		new->str = ft_strdup(str);
		if (new->str == NULL)
			return (NULL);
	}
	set_token_type(new);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	token_node_add_back(t_token *head, t_token *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
}

void	token_node_add_front(t_token *head, t_token *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head->next;
	new->prev = head;
	head->next->prev = new;
	head->next = new;
}

void	token_node_insert(t_token *node, t_token *new_node)
{
	t_token	*node_next;

	if (node == NULL || new_node == NULL)
		return ;
	node_next = node->next;
	node->next = new_node;
	new_node->next = node_next;
	new_node->prev = node;
	node_next->prev = new_node;
}

void	token_node_delete(t_token *target)
{
	t_token	*target_prev;
	t_token	*target_next;

	if (target == NULL)
		return ;
	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	free(target->str);
	target->str = NULL;
	free(target);
	target = NULL;
}
