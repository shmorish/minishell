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

static void	exit_numeric_error(char *str, t_data *data, t_proccess_type type)
{
	if (type == PARENT)
		ft_puterr("exit\n");
	ft_puterr("minishell: exit: ");
	ft_puterr(str);
	ft_puterr(": numeric argument required\n");
	data->exit_status = 255;
	exit (255);
}

static void	exit_arg_error(t_data *data, t_proccess_type type)
{
	if (type == PARENT)
		ft_puterr("exit\n");
	ft_puterr("minishell :exit: too many arguments\n");
	data->exit_status = 1;
}

static void	exit_number(char **array, t_env *env_head,
		t_data *data, t_proccess_type type)
{
	int	exit_code;

	if (is_long_overflow(array[1]))
		exit_numeric_error(array[1], data, type);
	else
	{
		if (!ft_strcmp("+", array[1]) || !ft_strcmp("-", array[1]))
			exit_numeric_error(array[1], data);
		exit_code = ft_atoi(array[1]);
		free_all(array, env_head);
		if (exit_code < 0)
		{
			while (exit_code < 0)
				exit_code += 256;
		}
		if (exit_code > 255)
			exit_code %= 256;
		if (type == PARENT)
			ft_puterr("exit\n");
		data->exit_status = exit_code;
		exit(exit_code);
	}
}

void	ft_exit(char **array, t_env *env_head,
			t_data *data, t_proccess_type type)
{
	if (array[1] == NULL || !ft_strcmp("--", array[1]))
	{
		free_all(array, env_head);
		if (type == PARENT)
			ft_puterr("exit\n");
		exit(data->exit_status);
	}
	if (!ft_is_number_str(array[1]))
		exit_numeric_error(array[1], data, type);
	if (array[2] != NULL)
		exit_arg_error(data, type);
	else
		exit_number(array, env_head, data, type);
}
