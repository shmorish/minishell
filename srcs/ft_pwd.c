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

#include "../includes/minishell.h"

void	ft_pwd(void)
{
	char	*path_name;

	path_name = ft_calloc(PATH_MAX, sizeof(char));
	if (path_name == NULL)
		return ;
	getcwd(path_name, PATH_MAX);
	if (path_name == NULL)
		ft_puterr(strerror(errno));
	else
		printf("%s\n", path_name);
	free(path_name);
}