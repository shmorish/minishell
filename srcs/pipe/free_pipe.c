/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:51:30 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/10 17:52:01 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipefd(int **pipefd)
{
	int	i;

	i = 0;
	while (pipefd[i] != NULL)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}
