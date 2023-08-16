/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:16:35 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 22:16:35 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char **list)
{
	int	ans;

	if (list[1] == NULL)
		chdir("/home/");
	else if (list[2] != NULL)
		ft_put_too_arg_err("cd");
	else
	{
		if (list[1][0] == '~')
			printf("~\n");
		if (!access(list[1], X_OK))
		{
			ans = chdir(list[1]);
			if (ans != 0)
				perror("cd");
		}
		else
			perror("cd");
	}
}