/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_node_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 10:31:17 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 16:09:25 by ryhara           ###   ########.fr       */
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
			free_token_head_all(head);
			return (NULL);
		}
		token_node_add_back(head, new);
		i++;
	}
	return (head);
}

void	free_token_head_all(t_token *head)
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
		free(delete->str);
		delete->str = NULL;
		free(delete);
		delete = NULL;
	}
	free(head->str);
	head->str = NULL;
	free(head);
	head = NULL;
}
