/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:16:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 15:51:03 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	path_free(char **path_list)
{
	int	i;

	i = 0;
	if (path_list == NULL)
		return ;
	while (path_list[i])
	{
		free(path_list[i]);
		path_list[i] = NULL;
		i++;
	}
	free(path_list);
	path_list = NULL;
}

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
		path_free(path_list);
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
			data->exit_status = 126;
		path_free(path_list);
		return (true);
	}
	else
		return (false);
}

char	*check_path_access(char **path_list, char *command, t_data *data)
{
	int		i;
	char	*joined_path;

	if (check_simple_access(path_list, command, data))
		return (command);
	if (path_list == NULL)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		joined_path = path_join(path_list, command, i);
		if (check_simple_access(path_list, joined_path, data))
			return (joined_path);
		i++;
		free(joined_path);
	}
	path_free(path_list);
	return (NULL);
}
