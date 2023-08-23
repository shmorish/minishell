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

#include "../../includes/minishell.h"

static void	ft_exit_number(char **list, t_env *env_head)
{
	int	exit_code;

	exit_code = ft_atoi(list[1]);
	free_all(list, env_head);
	if (exit_code < 0)
	{
		while (exit_code < 0)
			exit_code += 256;
	}
	if (exit_code > 255)
		exit_code %= 256;
	printf("exit\n");
	exit(exit_code);
}

void	ft_exit(char **list, t_env *env_head)
{
	if (list[1] == NULL)
	{
		free_all(list, env_head);
		printf("exit\n");
		exit(0);
	}
	if (!ft_is_number_str(list[1]))
	{
		printf("exit\n");
		ft_puterr("exit: ");
		ft_puterr(list[1]);
		ft_puterr(": numeric argument required\n");
		exit (255);
	}
	if (list[2] != NULL)
	{
		printf("exit\n");
		ft_puterr("exit: too many arguments\n");
		return ;
	}
	else
		ft_exit_number(list, env_head);
}
