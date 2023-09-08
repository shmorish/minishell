/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmorish <shmorish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:22:01 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/08 17:30:13 by shmorish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_parser_cmd(t_parser **tmp)
{
	int	i;

	i = 0;
	while ((*tmp)->cmd[i] != NULL)
	{
		free((*tmp)->cmd[i]);
		i++;
	}
	free((*tmp)->cmd);
	return (NULL);
}

void	*free_dup_null(char **tmp_cmd)
{
	int	i;

	i = 0;
	while (tmp_cmd[i] != NULL)
	{
		free(tmp_cmd[i]);
		i++;
	}
	free(tmp_cmd);
	return (NULL);
}

void	*free_dup_cmd_null(char **tmp_cmd, t_parser **tmp)
{
	free_dup_null(tmp_cmd);
	free_parser_cmd(tmp);
	return (NULL);
}
