/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:33:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/23 18:23:28 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_in_other_command(char **list, t_env *env_head, char *command)
{
	if (command != list[0])
		free(command);
	free_all(list, env_head);
}

static void	exe_command(char *command, char **list, t_env *env_head)
{
	int	exe_ans;

	exe_ans = execve(command, list, NULL);
	if (exe_ans < 0)
	{
		perror(command);
		free_in_other_command(list, env_head, command);
		exit(1);
	}
	free_in_other_command(list, env_head, command);
	exit(0);
}

static void	wait_in_other_command(char **list, t_env *env_head, char *command)
{
	int	status;

	if (wait(&status) < 0)
	{
		perror("wait");
		free_in_other_command(list, env_head, command);
		exit(1);
	}
	if (command != list[0])
		free(command);
}

void	ft_other_command(char **list, t_env *env_head)
{
	pid_t	pid;
	char	*command;

	command = check_path_access(path_split(get_env_var(env_head, "PATH")),
			list[0]);
	if (command == NULL)
	{
		ft_put_command_err(list[0]);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_in_other_command(list, env_head, command);
		exit(1);
	}
	if (pid == 0)
		exe_command(command, list, env_head);
	else
		wait_in_other_command(list, env_head, command);
}

// command not found ->  exit 127