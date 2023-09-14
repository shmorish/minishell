/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:16:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/14 14:25:46 by ryhara           ###   ########.fr       */
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

	if (!ft_strncmp(command, "./", 2))
	{
		if (check_simple_access(path_list, command, data))
			return (command);
		free_char_array(path_list);
		return (NULL);
	}
	i = 0;
	while (path_list != NULL && path_list[i])
	{
		joined_path = path_join(path_list, command, i++);
		if (check_simple_access(path_list, joined_path, data))
			return (joined_path);
		free(joined_path);
	}
	if (ft_strncmp("./", command, 2) == 0
		&& check_simple_access(path_list, command, data))
		return (command);
	free_char_array(path_list);
	return (NULL);
}

bool	check_directory(char *command, char **array, t_data *data)
{
	struct stat	st;
	int			result;
	char		*str;

	if (command == NULL)
		str = array[0];
	else
		str = command;
	result = stat(str, &st);
	if (result == -1)
		return (false);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_puterr_isdir(str);
		return (data->exit_status = 126, true);
	}
	else if ((st.st_mode & S_IFMT) == S_IFREG)
		return (false);
	return (false);
}
