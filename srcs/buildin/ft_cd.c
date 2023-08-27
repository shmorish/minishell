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

#include "../../includes/minishell.h"

void	change_directory(char *name, t_env *env_head)
{
	if (!access(name, X_OK))
	{
		if (chdir(name) != 0)
			perror("cd");
		else
			set_pwd(env_head);
	}
	else
		perror("cd");
}

void	ft_cd_home_plus(char **list, t_env *env_head)
{
	char	*str;
	char	*substr;
	char	*joinstr;

	substr = ft_substr(list[1], 1, ft_strlen(list[1]));
	if (substr == NULL)
		return ;
	joinstr = ft_strjoin(get_env_var(env_head, "HOME"), substr);
	if (joinstr == NULL)
	{
		free(substr);
		return ;
	}
	str = list[1];
	list[1] = joinstr;
	free(str);
	change_directory(list[1], env_head);
}

void	ft_cd_home(t_env *env_head)
{
	char	*name;

	name = get_env_var(env_head, "HOME");
	if (name == NULL)
		ft_puterr("bash: cd: HOME not set\n");
	else
		change_directory(name, env_head);
}

void	ft_cd_old_pwd(t_env *env_head)
{
	char	*name;

	name = get_env_var(env_head, "OLDPWD");
	if (name == NULL)
		ft_puterr("bash: cd: OLDPWD not set\n");
	else
	{
		if (!access(name, X_OK))
		{
			if (chdir(name) != 0)
				perror("cd");
			else
				ft_printf("%s\n", name);
		}
		else
			perror("cd");
	}
}

void	ft_cd(char **list, t_env *env_head)
{
	if (list[1] == NULL || (!ft_strncmp(list[1], "~", 1) && list[2] == NULL))
	{
		if (list[1][1] != '\0')
			ft_cd_home_plus(list, env_head);
		else
			ft_cd_home(env_head);
	}
	else if (!ft_strcmp(list[1], "-") && list[2] == NULL)
		ft_cd_old_pwd(env_head);
	else
		change_directory(list[1], env_head);
}
