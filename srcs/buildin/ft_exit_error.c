/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:45:34 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/17 10:27:59 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_numeric_error(char *str, t_data *data, t_proccess_type type)
{
	if (type == PARENT)
		ft_puterr("exit\n");
	ft_puterr("minishell: exit: ");
	ft_puterr(str);
	ft_puterr(": numeric argument required\n");
	free_env_head_all(data->env_head);
	data->exit_status = 255;
	exit (255);
}

void	exit_arg_error(t_data *data, t_proccess_type type)
{
	if (type == PARENT)
		ft_puterr("exit\n");
	ft_puterr("minishell :exit: too many arguments\n");
	data->exit_status = 1;
}
