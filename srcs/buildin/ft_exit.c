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

static void exit_numeric_error(char *str, t_data *data)
{
	ft_puterr("exit\n");
	ft_puterr("bash: exit: ");
	ft_puterr(str);
	ft_puterr(": numeric argument required\n");
	data->exit_status = 255;
	exit (255);
}

static void	exit_arg_error(t_data *data)
{
	ft_puterr("exit\n");
	ft_puterr("bash :exit: too many arguments\n");
	data->exit_status = 1;
}

static void	exit_number(char **list, t_env *env_head, t_data *data)
{
	int	exit_code;

	if (is_long_overflow(list[1]))
		exit_numeric_error(list[1], data);
	else
	{
		exit_code = ft_atoi(list[1]);
		free_all(list, env_head);
		if (exit_code < 0)
		{
			while (exit_code < 0)
				exit_code += 256;
		}
		if (exit_code > 255)
			exit_code %= 256;
		ft_puterr("exit\n");
		data->exit_status = exit_code;
		exit(exit_code);
	}
}

void	ft_exit(char **list, t_env *env_head, t_data *data)
{
	if (list[1] == NULL)
	{
		free_all(list, env_head);
		ft_puterr("exit\n");
		data->exit_status = 0;
		exit(0);
	}
	if (!ft_is_number_str(list[1]))
		exit_numeric_error(list[1], data);
	if (list[2] != NULL)
		exit_arg_error(data);
	else
		exit_number(list, env_head, data);
}
