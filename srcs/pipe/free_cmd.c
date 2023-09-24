/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:01:22 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/20 16:02:13 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(char **cmd)
{
	int	index;

	index = 0;
	if (cmd == NULL)
		return ;
	while (cmd[index] != NULL)
	{
		free(cmd[index]);
		cmd[index] = NULL;
		index++;
	}
	free(cmd);
	cmd = NULL;
}
