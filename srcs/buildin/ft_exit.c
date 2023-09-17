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

static void	exit_number(char *number, char **array,
		t_data *data, t_proccess_type type)
{
	int	exit_code;

	if (is_long_overflow(number))
		exit_numeric_error(number, data, type);
	else
	{
		if (!ft_strcmp("+", number) || !ft_strcmp("-", number))
			exit_numeric_error(number, data, type);
		exit_code = ft_atoi(number);
		free_all(array, data->env_head);
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

void	exit_main(char **array, t_data *data, t_proccess_type type)
{
	if (!ft_is_number_str(array[1]))
		exit_numeric_error(array[1], data, type);
	if (array[2] != NULL)
		exit_arg_error(data, type);
	else
		exit_number(array[1], array, data, type);
}

void	exit_include_space(char **array, char **new_array,
			t_data *data, t_proccess_type type)
{
	if (!ft_is_number_str(new_array[0]))
	{
		free_char_array(new_array);
		exit_numeric_error(array[1], data, type);
	}
	if (array[2] != NULL)
		exit_arg_error(data, type);
	else
		exit_number(new_array[0], new_array, data, type);
}

void	ft_exit(char **array, t_env *env_head,
			t_data *data, t_proccess_type type)
{
	char	**new_array;

	if (array[1] == NULL || !ft_strcmp("--", array[1]))
	{
		free_all(array, env_head);
		if (type == PARENT)
			ft_puterr("exit\n");
		exit(data->exit_status);
	}
	if (ft_strchr(array[1], ' '))
	{
		new_array = ft_split(array[1], ' ');
		if (new_array == NULL)
			exit(1);
		if (new_array[0] == NULL || new_array[1] != NULL)
			exit_main(array, data, type);
		else
			exit_include_space(array, new_array, data, type);
	}
	else
		exit_main(array, data, type);
}
