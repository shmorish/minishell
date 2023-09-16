/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:33:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 12:59:28 by ryhara           ###   ########.fr       */
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

	signal_child_init();
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

static void	wait_other_command(char **array, t_data *data, char *cmd, pid_t pid)
{
	int	status;

	signal_parent_init();
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("wait");
		free_in_other_command(array, data->env_head, cmd);
		data->exit_status = 1;
		exit(1);
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status);
	else
		data->exit_status = 1;
	if (cmd != array[0])
		free(cmd);
}

static void	exe_main(char *command, char **array, t_env *env_head, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_in_other_command(array, env_head, command);
		data->exit_status = 1;
		exit(1);
	}
	if (pid == 0)
		exe_command(command, array, data);
	else
		wait_other_command(array, data, command, pid);
}

void	ft_other_command(char **array, t_env *env_head, t_data *data)
{
	char	*command;
	char	**path_list;

	if (array[0][0] == '\0')
		return (ft_puterr_command(array[0], data));
	if (check_directory(array[0], data))
		return ;
	if (!ft_strncmp(array[0], "./", 2))
	{
		if (check_simple_access(NULL, array[0], data))
			command = array[0];
		else
			return (ft_puterr_permit(array[0]));
	}
	if (check_simple_access(NULL, array[0], data) && check_include_slash(array[0]))
		command = array[0];
	else
	{
		path_list = path_split(get_env_val(env_head, "PATH"));
		if (path_list == NULL)
			return ;
		command = check_path_access(path_list, array[0], data);
		if (command == NULL)
			return (ft_puterr_command(array[0], data));
	}
	exe_main(command, array, env_head, data);
}

// void	ft_other_command(char **array, t_env *env_head, t_data *data)
// {
// 	char	*command;

// 	if (array[0][0] == '\0')
// 	{
// 		ft_puterr_command(array[0], data);
// 		return ;
// 	}
// 	data->exit_status = 0;
// 	command = check_path_access(path_split(get_env_val(env_head, "PATH")),
// 			array[0], data);
// 	if (data->exit_status == 126 && !ft_strncmp("./", array[0], 2)
// 		&& access(array[0], X_OK))
// 		return (ft_puterr_permit(array[0]));
// 	if (check_directory(command, array, data))
// 		return ;
// 	if (command == NULL)
// 	{
// 		ft_puterr_command(array[0], data);
// 		return ;
// 	}
// 	exe_main(command, array, env_head, data);
// }
