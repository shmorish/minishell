/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:35:14 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 18:59:26 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	get_env_list_size(t_env *env_head)
{
	t_env	*tmp_node;
	size_t	count;

	tmp_node = env_head->next;
	count = 0;
	while (tmp_node != env_head)
	{
		count++;
		tmp_node = tmp_node->next;
	}
	return (count);
}

char	*join_env_path(char **array, t_env *node)
{
	char	*join_env_name;
	char	*join_path;

	join_env_name = ft_strjoin(node->env_name, "=");
	if (join_env_name == NULL)
	{
		free_char_array(array);
		return (NULL);
	}
	join_path = ft_strjoin(join_env_name, node->env_val);
	if (join_path == NULL)
	{
		free_char_array(array);
		free(join_env_name);
		return (NULL);
	}
	free(join_env_name);
	return (join_path);
}

char	**env_list_to_char_arr(t_env *env_head)
{
	t_env	*tmp_node;
	char	*join_path;
	char	**array;
	size_t	index;

	array = (char **)malloc(sizeof(char *) * (get_env_list_size(env_head) + 1));
	if (array == NULL)
		return (NULL);
	index = 0;
	tmp_node = env_head->next;
	while (tmp_node != env_head)
	{
		join_path = join_env_path(array, tmp_node);
		if (join_path == NULL)
			return (NULL);
		array[index] = join_path;
		index++;
		tmp_node = tmp_node->next;
	}
	array[index] = NULL;
	return (array);
}
