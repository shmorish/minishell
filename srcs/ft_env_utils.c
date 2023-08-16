/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:16:01 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 23:16:01 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*node_new(char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
		new->var = NULL;
	else
	{
		new->var = ft_strdup(str);
		if (new->var == NULL)
			return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

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
	free(target->var);
	target->var = NULL;
	free(target);
	target = NULL;
}

t_env	*get_node_pos(t_env *head, char *str)
{
	size_t	count;
	t_env	*tmp;

	count = 0;
	tmp = head->next;
	while (str[count] != '=' && str[count] != '\0')
		count++;
	while (tmp != head)
	{
		if (!ft_strncmp(str, tmp->var, count))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
