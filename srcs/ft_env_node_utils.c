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
	char	**path_list;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
	{
		new->env_name = NULL;
		new->env_var = NULL;
	}
	else
	{
		path_list = ft_split(str, '=');
		if (path_list == NULL)
			return (NULL);
		new->env_name = path_list[0];
		if (path_list[1] == NULL)
			new->env_var = ft_strdup("");
		else
			new->env_var = path_list[1];
		free(path_list);
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
	node_free(target);
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
		if (!ft_strncmp(str, tmp->env_name, count))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
