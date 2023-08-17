/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:33:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/17 13:06:02 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_other_command(char **list, t_env *env_head)
{
	pid_t	pid;
	int		ans;
	int		ret;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_all(list, env_head);
		exit(2);
	}
	else if (pid == 0)
	{
		ans = execve(list[0], list, NULL);
		if (ans == -1)
		{
			ft_put_command_err(list[0]);
			free_all(list, env_head);
			exit(1);
		}
		printf("\n");
		free_all(list, env_head);
		exit(0);
	}
	if ((ret = wait(&status)) < 0)
	{
		perror("wait");
		free_all(list, env_head);
		exit(4);
	}
}