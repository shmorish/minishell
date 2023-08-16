/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 23:56:06 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 23:56:06 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*head_init(void)
{
	t_env	*head;

	head = node_new("");
	if (head == NULL)
		return (NULL);
	head->next = head;
	head->prev = head;
	return (head);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;

	i = 0;
	head = head_init();
	while (envp[i])
	{
		new = node_new(envp[i]);
		if (new == NULL)
		{
			head_free_all(head);
			return (NULL);
		}
		node_add_back(head, new);
		i++;
	}
	return (head);
}
