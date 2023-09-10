/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:56:22 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 22:56:22 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **array, t_env *env_head, t_data *data)
{
	t_env	*tmp;

	if (array[1] != NULL)
	{
		ft_puterr_env(array[1]);
		data->exit_status = 127;
	}
	else
	{
		tmp = env_head->next;
		while (tmp != env_head)
		{
			ft_printf("%s=%s\n", tmp->env_name, tmp->env_val);
			tmp = tmp->next;
		}
		data->exit_status = 0;
	}
}
