/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:32:13 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 23:32:13 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		list[i] = NULL;
		i++;
	}
	free(list);
	list = NULL;
}

void	node_free(t_env *node)
{
	free(node->env_name);
	node->env_name = NULL;
	free(node->env_var);
	node->env_var = NULL;
	free(node);
	node = NULL;
}

void	head_free_all(t_env *head)
{
	t_env	*tmp;
	t_env	*delete;

	if (head == NULL)
		return ;
	tmp = head->next;
	while (tmp != head)
	{
		delete = tmp;
		head->next = tmp->next;
		tmp->next->prev = head;
		tmp = tmp->next;
		node_free(delete);
	}
	node_free(head);
}

void	free_all(char **list, t_env *head)
{
	free_list(list);
	head_free_all(head);
}