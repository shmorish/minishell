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

#include "../includes/minishell.h"

void	select_commands(char **list, t_env *env_head)
{
	if (!ft_strcmp("echo", list[0]))
		ft_echo(list);
	else if (!ft_strcmp("exit", list[0]))
		ft_exit(list, env_head);
	else if (!ft_strcmp("pwd", list[0]))
		ft_pwd();
	else if (!ft_strcmp("cd", list[0]))
		ft_cd(list, env_head);
	else if (!ft_strcmp("env", list[0]))
		ft_env(list, env_head);
	else if (!ft_strcmp("export", list[0]))
		ft_export(list, env_head);
	else if (!ft_strcmp("unset", list[0]))
		ft_unset(list, env_head);
	else
		ft_other_command(list, env_head);
		// ft_put_command_err(list[0]);
}
