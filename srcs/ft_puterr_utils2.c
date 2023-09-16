/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:52:32 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 16:20:14 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_puterr_env(char *s)
{
	ft_puterr("env: ");
	ft_puterr(s);
	ft_puterr(": No such file or directory\n");
}

void	ft_strerror_cd(char *str, int number, t_data *data)
{
	ft_puterr("minishell: cd: ");
	ft_puterr(str);
	ft_puterr(": ");
	ft_puterr(strerror(errno));
	ft_puterr("\n");
	data->exit_status = number;
}

void	ft_puterr_malloc(void)
{
	ft_puterr("\033[31m malloc error\n \033[0m");
	exit(1);
}

void	ft_puterr_nofile(char *s)
{
	ft_puterr("minishell: ");
	ft_puterr(s);
	ft_puterr(": No such file or directory\n");
}

void	ft_puterr_isdir(char *s)
{
	ft_puterr("minishell: ");
	ft_puterr(s);
	ft_puterr(": is a directory\n");
}
