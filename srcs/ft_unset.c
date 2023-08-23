/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:29:40 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/13 16:29:40 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(char **list, t_env *env_head)
{
	int	i;

	if (list[1] == NULL)
		;
	else
	{
		i = 1;
		while (list[i])
		{
			if (check_duplicate_path(list[i], env_head))
				node_delete(get_node_pos(env_head, list[i]));
			i++;
		}
	}
}
