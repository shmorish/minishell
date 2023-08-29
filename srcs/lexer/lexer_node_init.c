/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_node_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:31:17 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/29 10:31:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*token_head_init(void)
{
	t_token	*head;

	head = token_node_new("");
	if (head == NULL)
		return (NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

t_token	*token_init(char **envp)
{
	t_token	*head;
	t_token	*new;
	int		i;

	i = 0;
	head = token_head_init();
	while (envp[i])
	{
		new = token_node_new(envp[i]);
		if (new == NULL)
		{
			token_head_free_all(head);
			return (NULL);
		}
		token_node_add_back(head, new);
		i++;
	}
	return (head);
}

void	token_head_free_all(t_token *head)
{
	t_token	*tmp;
	t_token	*delete;

	if (head == NULL)
		return ;
	tmp = head->next;
	while (tmp != head)
	{
		delete = tmp;
		head->next = tmp->next;
		tmp->next->prev = head;
		tmp = tmp->next;
		free(delete->data);
		delete->data = NULL;
		free(delete);
		delete = NULL;
	}
	free(head->data);
	head->data = NULL;
	free(head);
	head = NULL;
}
