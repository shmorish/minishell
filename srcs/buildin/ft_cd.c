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

static void	change_directory(char *name, t_env *env_head, t_data *data)
{
	set_pwd(env_head, "OLDPWD");
	if (chdir(name) != 0)
		ft_strerror_cd(name, 1, data);
	else
	{
		set_pwd(env_head, "PWD");
		data->exit_status = 0;
	}
}

static void	ft_cd_home_plus(char **array, t_env *env_head, t_data *data)
{
	char	*str;
	char	*substr;
	char	*joinstr;

	substr = ft_substr(array[1], 1, ft_strlen(array[1]));
	if (substr == NULL)
		return (ft_puterr_malloc());
	if (get_env_val(env_head, "HOME") == NULL)
	{
		free(substr);
		ft_puterr_set_status("minishell: cd: HOME not set\n", data, 1);
		return ;
	}
	joinstr = ft_strjoin(get_env_val(env_head, "HOME"), substr);
	if (joinstr == NULL)
	{
		free(substr);
		return (ft_puterr_malloc());
	}
	str = array[1];
	array[1] = joinstr;
	free(str);
	free(substr);
	change_directory(array[1], env_head, data);
}

static void	ft_cd_home(t_env *env_head, t_data *data)
{
	char	*name;

	name = get_env_val(env_head, "HOME");
	if (name == NULL)
		ft_puterr_set_status("minishell: cd: HOME not set\n", data, 1);
	else
		change_directory(name, env_head, data);
}

static void	ft_cd_old_pwd(t_env *env_head, t_data *data)
{
	char	*name;

	name = ft_strdup(get_env_val(env_head, "OLDPWD"));
	if (name == NULL)
		ft_puterr_set_status("minishell: cd: OLDPWD not set\n", data, 1);
	else
	{
		set_pwd(env_head, "OLDPWD");
		if (chdir(name) != 0)
			ft_strerror_cd(name, 1, data);
		else
		{
			ft_printf("%s\n", name);
			data->exit_status = 0;
		}
		free(name);
	}
}

void	ft_cd(char **array, t_env *env_head, t_data *data)
{
	if (array[1] == NULL)
		return (ft_cd_home(env_head, data));
	if (array[1][0] == '\0')
		return ;
	else if (!ft_strncmp(array[1], "~", 1))
	{
		if (array[1][1] != '\0')
			ft_cd_home_plus(array, env_head, data);
		else
			ft_cd_home(env_head, data);
	}
	else if (!ft_strcmp(array[1], "-"))
		ft_cd_old_pwd(env_head, data);
	else
		change_directory(array[1], env_head, data);
}
