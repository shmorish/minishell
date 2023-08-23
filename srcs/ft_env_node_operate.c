/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_node_operate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:18:31 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/22 19:23:11 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	node_add_back(t_env *head, t_env *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head;
	new->prev = head->prev;
	head->prev->next = new;
	head->prev = new;
}

void	node_add_front(t_env *head, t_env *new)
{
	if (head == NULL || new == NULL)
		return ;
	new->next = head->next;
	new->prev = head;
	head->next->prev = new;
	head->next = new;
}

void	node_delete(t_env *target)
{
	t_env	*target_prev;
	t_env	*target_next;

	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	node_free(target);
}
