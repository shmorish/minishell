/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:15:24 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 15:15:24 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env	*node_new_set(t_env *new, char *str)
{
	char	**path_list;

	path_list = ft_split_once(str, '=');
	if (path_list == NULL)
		return (NULL);
	new->env_name = path_list[0];
	if (path_list[1] == NULL)
		new->env_val = ft_strdup("");
	else
		new->env_val = path_list[1];
	free(path_list);
	return (new);
}

t_env	*node_new(char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
	{
		new->env_name = NULL;
		new->env_val = NULL;
	}
	else
	{
		new = node_new_set(new, str);
		if (new == NULL)
			return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static t_env	*node_new_set_with_plus(t_env *new, char *str)
{
	char	**path_list;

	path_list = ft_split_once(str, '=');
	if (path_list == NULL)
		return (NULL);
	new->env_name = ft_strccpy(path_list[0], '+');
	if (new->env_name == NULL)
	{
		free(path_list);
		return (NULL);
	}
	new->env_val = path_list[1];
	free(path_list);
	return (new);
}

t_env	*node_new_with_plus(char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	if (ft_strlen(str) == 0)
	{
		new->env_name = NULL;
		new->env_val = NULL;
	}
	else
	{
		new = node_new_set_with_plus(new, str);
		if (new == NULL)
			return (NULL);
	}
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
