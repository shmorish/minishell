/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:16:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/12 13:40:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*path_join(char **path_list, char *command, int pos)
{
	char	*path_join;
	char	*slash_join;

	slash_join = ft_strjoin(path_list[pos], "/");
	if (slash_join == NULL)
		return (NULL);
	path_join = ft_strjoin(slash_join, command);
	free(slash_join);
	if (path_join == NULL)
	{
		free_char_array(path_list);
		return (NULL);
	}
	return (path_join);
}

char	**path_split(char *path)
{
	char	**path_list;

	if (path == NULL)
		return (NULL);
	path_list = ft_split(path, ':');
	if (path_list == NULL)
		return (NULL);
	return (path_list);
}

static bool	check_simple_access(char **path_list, char *command, t_data *data)
{
	if (!access(command, F_OK))
	{
		if (access(command, X_OK))
		{
			data->exit_status = 126;
			return (false);
		}
		free_char_array(path_list);
		return (true);
	}
	else
		return (false);
}

char	*check_path_access(char **path_list, char *command, t_data *data)
{
	int		i;
	char	*joined_path;

	if (path_list == NULL)
		return (NULL);
	if (!ft_strncmp(command, "./", 2))
	{
		if (check_simple_access(path_list, command, data))
			return (command);
		free_char_array(path_list);
		return (NULL);
	}
	i = 0;
	while (path_list[i])
	{
		joined_path = path_join(path_list, command, i++);
		if (check_simple_access(path_list, joined_path, data))
			return (joined_path);
		free(joined_path);
	}
	if (check_simple_access(path_list, command, data))
		return (command);
	free_char_array(path_list);
	return (NULL);
}

bool	check_directory(char **array, t_data *data)
{
	size_t	i;
	bool	flag;

	i = 0;
	flag = false;
	while (array[0][i])
	{
		if (array[0][i] == '/')
			flag = true;
		i++;
	}
	if (flag)
	{
		if (!access(array[0], F_OK))
		{
			ft_puterr_isdir(array[0]);
			data->exit_status = 126;
			return (true);
		}
		data->exit_status = 127;
		ft_puterr_nofile(array[0]);
		return (true);
	}
	else
		return (false);
}
