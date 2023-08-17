/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:29:19 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/17 12:58:44 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_puterr(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
}

void	ft_put_command_err(char *s)
{
	ft_puterr(s);
	ft_puterr(": command not found\n");
}

void	ft_put_too_arg_err(char *s)
{
	ft_puterr(s);
	ft_puterr(": too many arguments\n");
}

void	ft_put_few_arg_err(char *s)
{
	ft_puterr(s);
	ft_puterr(": not enough arguments\n");
}
