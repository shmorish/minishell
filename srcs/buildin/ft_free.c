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

void	free_char_array(char **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_env_node(t_env *node)
{
	free(node->env_name);
	node->env_name = NULL;
	free(node->env_val);
	node->env_val = NULL;
	free(node);
	node = NULL;
}

void	free_env_head_all(t_env *head)
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
		free_env_node(delete);
	}
	free_env_node(head);
}

void	free_all(char **array, t_env *head)
{
	free_char_array(array);
	free_env_head_all(head);
}
