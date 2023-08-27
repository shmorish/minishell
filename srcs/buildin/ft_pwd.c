/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 22:04:21 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/12 22:04:21 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd(void)
{
	char	*path_name;

	path_name = ft_calloc(PATH_MAX, sizeof(char));
	if (path_name == NULL)
		return (NULL);
	if (getcwd(path_name, PATH_MAX) == NULL)
		return (NULL);
	else
		return (path_name);
	free(path_name);
}

void	create_pwd(t_env *env_head)
{
	char	*tmp_str;
	char	*path_name;

	path_name = get_pwd();
	if (path_name == NULL)
		return ;
	tmp_str = ft_strjoin("PWD=", path_name);
	if (tmp_str == NULL)
		return ;
	node_add_back(env_head, node_new(tmp_str));
}

void	update_pwd(t_env *node)
{
	char	*tmp_str;
	char	*path_name;

	free(node->env_var);
	path_name = get_pwd();
	if (path_name == NULL)
		return ;
	tmp_str = ft_strdup(path_name);
	if (tmp_str == NULL)
		;
	else
		node->env_var = tmp_str;
	free(path_name);
}

void	set_pwd(t_env *env_head)
{
	t_env	*tmp_node;

	tmp_node = get_node_pos(env_head, "PWD");
	if (tmp_node == NULL)
		create_pwd(env_head);
	else
		update_pwd(tmp_node);
}

void	ft_pwd(void)
{
	char	*path_name;

	path_name = ft_calloc(PATH_MAX, sizeof(char));
	if (path_name == NULL)
		return ;
	if (getcwd(path_name, PATH_MAX) == NULL)
	{
		ft_puterr(strerror(errno));
		ft_puterr("\n");
	}
	else
		ft_printf("%s\n", path_name);
	free(path_name);
}
