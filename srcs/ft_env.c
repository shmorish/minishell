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

#include "minishell.h"

void	ft_env(char **list, t_env *env_head)
{
	t_env	*tmp;

	if (list[1] != NULL)
		ft_put_too_arg_err("env");
	else
	{
		tmp = env_head->next;
		while (tmp != env_head)
		{
			printf("%s=%s\n", tmp->env_name, tmp->env_var);
			tmp = tmp->next;
		}
	}
}
