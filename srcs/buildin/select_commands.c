/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:41:09 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 21:41:09 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	select_commands(char **array, t_env *env_head, t_data *data,
		t_proccess_type type)
{

	if (!ft_strcmp("echo", array[0]))
		ft_echo(array, data);
	else if (!ft_strcmp("exit", array[0]))
		ft_exit(array, env_head, data, type);
	else if (!ft_strcmp("pwd", array[0]))
		ft_pwd(data);
	else if (!ft_strcmp("cd", array[0]))
		ft_cd(array, env_head, data);
	else if (!ft_strcmp("env", array[0]))
		ft_env(array, env_head, data);
	else if (!ft_strcmp("export", array[0]))
		ft_export(array, env_head, data);
	else if (!ft_strcmp("unset", array[0]))
		ft_unset(array, env_head, data);
	else
		ft_other_command(array, env_head, data);
}
