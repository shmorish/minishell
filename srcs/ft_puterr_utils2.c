/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:52:32 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/04 20:37:42 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_puterr_env(char *s)
{
	ft_puterr("env: ");
	ft_puterr(s);
	ft_puterr(": No such file or directory\n");
}

void	ft_perror_set_status(char *str, int number, t_data *data)
{
	perror(str);
	data->exit_status = number;
}

void	*ft_puterr_malloc(void)
{
	ft_puterr("\033[31m malloc error\n \033[0m");
	return (NULL);
}