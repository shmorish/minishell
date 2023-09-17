/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_operate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:18:31 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/17 13:24:17 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (target == NULL)
		return ;
	target_next = target->next;
	target_prev = target->prev;
	target_prev->next = target_next;
	target_next->prev = target_prev;
	free_env_node(target);
}

t_env	*get_node_pos(t_env *head, char *str)
{
	size_t	count;
	t_env	*tmp;
	char	*path_name;

	count = 0;
	tmp = head->next;
	while (str[count] != '=' && str[count] != '\0')
		count++;
	if (str[count - 1] == '+')
		count--;
	path_name = ft_substr(str, 0, count);
	if (path_name == NULL)
		return (ft_puterr_malloc(), NULL);
	while (tmp != head)
	{
		if (!ft_strcmp(path_name, tmp->env_name))
		{
			free(path_name);
			path_name = NULL;
			return (tmp);
		}
		tmp = tmp->next;
	}
	free(path_name);
	return (NULL);
}

char	*get_env_val(t_env *env_head, char *env_name)
{
	t_env	*tmp;

	if (env_head == NULL)
		return (NULL);
	tmp = env_head->next;
	while (tmp != env_head)
	{
		if (!ft_strcmp(tmp->env_name, env_name))
			return (tmp->env_val);
		tmp = tmp->next;
	}
	return (NULL);
}
