/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:25:38 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/27 17:25:56 by ryhara           ###   ########.fr       */
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

char	*check_path_access(char **path_list, char *command)
{
	int		i;
	char	*joined_path;

	if (!access(command, X_OK))
	{
		path_free(path_list);
		return (command);
	}
	if (path_list == NULL)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		joined_path = path_join(path_list, command, i);
		if (!access(joined_path, X_OK))
		{
			path_free(path_list);
			return (joined_path);
		}
		i++;
		free(joined_path);
	}
	path_free(path_list);
	return (NULL);
}
