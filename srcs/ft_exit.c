/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:31:26 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 17:31:26 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char **list, t_env *env_head)
{
	int	exit_code;

	if (list[1] == NULL)
	{
		free_all(list, env_head);
		exit(0);
	}
	if (list[2] != NULL)
	{
		ft_puterr("Too many arguments\n");
		return ;
	}
	if (!ft_is_number_str(list[1]))
	{
		ft_puterr("Not valid exit code\n");
		return ;
	}
	else
	{
		exit_code = ft_atoi(list[1]);
		free_all(list, env_head);
		exit(exit_code);
	}
}
