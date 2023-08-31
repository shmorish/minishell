/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:33:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 18:59:54 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_in_other_command(char **array, t_env *env_head, char *command)
{
	if (command != array[0])
		free(command);
	free_all(array, env_head);
}

static void	exe_command(char *command, char **array, t_data *data)
{
	int	exe_ans;

	exe_ans = execve(command, array, env_list_to_char_arr(data->env_head));
	if (exe_ans < 0)
	{
		perror(command);
		free_in_other_command(array, data->env_head, command);
		data->exit_status = 1;
		exit(1);
	}
	free_in_other_command(array, data->env_head, command);
	data->exit_status = 0;
	exit(0);
}

static void	wait_in_other_command(char **array, t_env *env_head, char *command)
{
	int	status;

	if (wait(&status) < 0)
	{
		perror("wait");
		free_in_other_command(array, env_head, command);
		exit(1);
	}
	if (command != array[0])
		free(command);
}

static void	exe_main(char *command, char **array, t_env *env_head, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_in_other_command(array, env_head, command);
		exit(1);
	}
	if (pid == 0)
		exe_command(command, array, data);
	else
		wait_in_other_command(array, env_head, command);
}

void	ft_other_command(char **array, t_env *env_head, t_data *data)
{
	char	*command;

	command = check_path_access(path_split(get_env_val(env_head, "PATH")),
			array[0], data);
	if (data->exit_status == 126)
	{
		ft_puterr_permit(array[0]);
		return ;
	}
	if (command == NULL)
	{
		ft_puterr_command(array[0], data);
		return ;
	}
	exe_main(command, array, env_head, data);
}
