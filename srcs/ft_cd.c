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

void	ft_cd_home(t_env *env_head)
{
	int		ans;
	char	*name;

	name = get_env_var(env_head, "HOME");
	if (name == NULL)
		ft_puterr("cd: can't find HOME\n");
	else
	{
		if (!access(name, X_OK))
		{
			ans = chdir(name);
			if (ans != 0)
				perror("cd");
		}
		else
			perror("cd");
	}
}

void	ft_cd_old_pwd(t_env *env_head)
{
	int		ans;
	char	*name;

	name = get_env_var(env_head, "OLDPWD");
	if (name == NULL)
		ft_puterr("cd: can't find OLDPWD\n");
	else
	{
		if (!access(name, X_OK))
		{
			ans = chdir(name);
			if (ans != 0)
				perror("cd");
			else
				printf("%s\n", name);
		}
		else
			perror("cd");
	}
}

void	ft_cd(char **list, t_env *env_head)
{
	if (list[1] == NULL || (!ft_strcmp(list[1], "~") && list[2] == NULL))
	{
		ft_cd_home(env_head);
		return ;
	}
	else if (!ft_strcmp(list[1], "-") && list[2] == NULL)
	{
		ft_cd_old_pwd(env_head);
		return ;
	}
	else
	{
		if (!access(list[1], X_OK))
		{
			if (chdir(list[1]) != 0)
				perror("cd");
		}
		else
			perror("cd");
	}
}
