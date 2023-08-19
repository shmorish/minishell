/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:33:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/19 12:46:33 by ryhara           ###   ########.fr       */
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
	if (pid == 0)
	{
		ans = execve(list[0], list, NULL);
		if (ans < 0)
		{
			ft_put_command_err(list[0]);
			free_all(list, env_head);
			exit(1);
		}
		printf("\n");
		free_all(list, env_head);
		exit(0);
	}
	else
	{
		ret = wait(&status);
		if (ret < 0)
		{
			perror("wait");
			free_all(list, env_head);
			exit(4);
		}
	}

}