/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:04:48 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/13 16:04:48 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_export(t_env *env_head)
{
	t_env	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		printf("declare -x %s=\"%s\"\n", tmp->env_name, tmp->env_var);
		tmp = tmp->next;
	}
}

static void	ft_export_with_plus(char **list, t_env *env_head, int pos)
{
	if (check_duplicate_path(list[pos], env_head))
		join_path(list[pos], get_node_pos(env_head, list[pos]));
	else
		node_add_back(env_head, node_new_with_plus(list[pos]));
}

static void	ft_export_default(char **list, t_env *env_head, int pos)
{
	if (check_duplicate_path(list[pos], env_head))
		change_path(list[pos], get_node_pos(env_head, list[pos]));
	else
		node_add_back(env_head, node_new(list[pos]));
}

void	ft_export(char **list, t_env *env_head)
{
	int		i;

	if (list[1] == NULL)
		put_export(env_head);
	else
	{
		i = 1;
		while (list[i])
		{
			if (check_equal(list[i]))
			{
				if (check_plus(list[i]))
					ft_export_with_plus(list, env_head, i);
				else
					ft_export_default(list, env_head, i);
			}
			else
				ft_put_not_valid("export", list[i]);
			i++;
		}
	}
}
