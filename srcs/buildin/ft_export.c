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

#include "../../includes/minishell.h"

static void	export_put(t_env *env_head)
{
	t_env	*tmp;

	tmp = env_head->next;
	while (tmp != env_head)
	{
		ft_printf("declare -x %s=\"%s\"\n", tmp->env_name, tmp->env_val);
		tmp = tmp->next;
	}
}

static void	export_with_plus(char **array, t_env *env_head, int pos)
{
	if (check_duplicate_path(array[pos], env_head))
		join_path(array[pos], get_node_pos(env_head, array[pos]));
	else
		node_add_back(env_head, node_new_with_plus(array[pos]));
}

static void	export_default(char **array, t_env *env_head, int pos)
{
	if (check_duplicate_path(array[pos], env_head))
		change_path(array[pos], get_node_pos(env_head, array[pos]));
	else
		node_add_back(env_head, node_new(array[pos]));
}

static bool	export_check(char **array, t_env *env_head, t_data *data)
{
	int		i;
	bool	error_flag;

	i = 1;
	error_flag = false;
	while (array[i])
	{
		if (check_equal(array[i]))
		{
			if (!ft_strchr(array[i], '='))
				;
			else if (check_plus(array[i]))
				export_with_plus(array, env_head, i);
			else
				export_default(array, env_head, i);
			data->exit_status = 0;
		}
		else
		{
			ft_puterr_valid_identifer("export", array[i], data);
			error_flag = true;
		}
		i++;
	}
	return (error_flag);
}

void	ft_export(char **array, t_env *env_head, t_data *data)
{
	bool	error_flag;

	error_flag = false;
	if (array[1] == NULL)
		export_put(env_head);
	else
		error_flag = export_check(array, env_head, data);
	if (error_flag == false)
		data->exit_status = 0;
}
