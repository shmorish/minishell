/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:23:51 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 16:14:11 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_duplicate_path(char *str, t_env *env_head)
{
	size_t	count;
	t_env	*tmp;

	count = 0;
	tmp = env_head->next;
	while (str[count] != '=' && str[count] != '\0')
		count++;
	if (str[count - 1] == '+')
		count--;
	while (tmp != env_head)
	{
		if (!ft_strncmp(str, tmp->env_name, count))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

void	change_path(char *str, t_env *target)
{
	char	**path_list;

	path_list = ft_split_once(str, '=');
	if (path_list == NULL)
		return ;
	free(target->env_val);
	if (path_list[1] == NULL)
	{
		free(path_list[1]);
		target->env_val = ft_strdup("");
	}
	else
		target->env_val = path_list[1];
	free(path_list[0]);
	free(path_list);
}

void	join_path(char *str, t_env *target)
{
	char	**path_list;
	char	*join_str;

	path_list = ft_split_once(str, '=');
	if (path_list == NULL)
		return ;
	if (path_list[1] == NULL)
		free(path_list[1]);
	else
	{
		join_str = ft_strjoin(target->env_val, path_list[1]);
		free(target->env_val);
		free(path_list[1]);
		if (join_str == NULL)
			return ;
		target->env_val = join_str;
	}
	free(path_list[0]);
	free(path_list);
}

bool	check_equal(char *str)
{
	bool	ans;
	size_t	i;

	ans = false;
	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		;
	else
		return (ans);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=')
			;
		else
		{
			if (str[i] == '+' && (str[i + 1] == '='))
				ans = true;
			else
				return (false);
		}
		if (str[i] == '=' && i != 0)
			return (true);
		i++;
	}
	return (ans);
}

bool	check_plus(char *str)
{
	bool	ans;
	size_t	i;

	ans = false;
	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i - 1] == '+')
		ans = true;
	return (ans);
}
