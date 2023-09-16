/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:16:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 12:02:49 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_join(char **path_list, char *command, int pos)
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
