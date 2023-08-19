/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:04:48 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/13 16:04:48 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	check_equal(char *str)
{
	bool	ans;
	size_t	i;

	ans = false;
	i = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '=')
			;
		else
		{
			if (str[i] == '+' && (str[i - 1] == '=' || str[i + 1] == '='))
				ans = true;
			else
				return (false);
		}
		if (str[i] == '=' && i != 0)
			ans = true;
		i++;
	}
	return (ans);
}

bool	check_duplicate_path(char *str, t_env *env_head)
{
	size_t	count;
	t_env	*tmp;

	count = 0;
	tmp = env_head->next;
	while (str[count] != '=' && str[count] != '\0')
		count++;
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

	path_list = ft_split(str, '=');
	if (path_list == NULL)
		return ;
	free(target->env_var);
	if (path_list[1] == NULL)
	{
		free(path_list[1]);
		target->env_var = ft_strdup("");
	}
	else
		target->env_var = path_list[1];
	free(path_list[0]);
	free(path_list);
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

void	ft_export(char **list, t_env *env_head)
{
	int		i;

	if (list[1] == NULL)
		ft_put_few_arg_err("export");
	else
	{
		i = 1;
		while (list[i])
		{
			if (check_equal(list[i]))
			{
				if (check_plus(list[i]))
				{
					if (check_duplicate_path(list[i], env_head))
					{
						// join
						;
					}
					else
						node_add_back(env_head, node_new(list[i]));
				}
				else
				{
					if (check_duplicate_path(list[i], env_head))
						change_path(list[i], get_node_pos(env_head, list[i]));
					else
						node_add_back(env_head, node_new(list[i]));
				}
			}
			else
				ft_puterr("export: error\n");
			i++;
		}
	}
}
