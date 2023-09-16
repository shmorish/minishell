/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:00:02 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 16:39:33 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_simple_access(char **path_list, char *command, t_data *data)
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

bool	check_directory(char *command, t_data *data)
{
	struct stat	st;
	int			result;

	result = stat(command, &st);
	if (result == -1)
		return (false);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_puterr_isdir(command);
		return (data->exit_status = 126, true);
	}
	else if ((st.st_mode & S_IFMT) == S_IFREG)
		return (false);
	return (false);
}

bool	check_include_slash(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

void	check_permit(char **array, t_data *data, char **command)
{
	if (array[0][0] == '\0')
		return (ft_puterr_command(array[0], data));
	if (check_directory(array[0], data))
		return ;
	if (!ft_strncmp(array[0], "./", 2))
	{
		if (check_simple_access(NULL, array[0], data))
			*command = array[0];
		else
			return (ft_puterr_permit(array[0]));
	}
}
