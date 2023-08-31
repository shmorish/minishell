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
			if (check_duplicate_path(array[i], env_head))
				node_delete(get_node_pos(env_head, array[i]));
			else
			{
				ft_puterr_valid_identifer("unset", array[i], data);
				error_flag = true;
			}
			i++;
		}
	}
	if (error_flag == false)
		data->exit_status = 0;
}
