/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:29:40 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/13 16:29:40 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	unset_check_name(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '_' || ft_isalpha(str[i]))
	{
		i++;
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (str[i] == '\0')
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

void	ft_unset(char **array, t_env *env_head, t_data *data)
{
	int		i;
	bool	error_flag;

	error_flag = false;
	if (array[1] == NULL)
		data->exit_status = 0;
	else
	{
		i = 1;
		while (array[i])
		{
			if (!unset_check_name(array[i]))
			{
				ft_puterr_valid_identifer("unset", array[i], data);
				error_flag = true;
			}
			else if (check_duplicate_path(array[i], env_head))
				node_delete(get_node_pos(env_head, array[i]));
			i++;
		}
	}
	if (error_flag == false)
		data->exit_status = 0;
}
