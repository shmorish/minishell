/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:29:19 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/27 15:58:45 by ryhara           ###   ########.fr       */
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

void	ft_put_not_valid(char *command, char *s)
{
	ft_puterr("bash: ");
	ft_puterr(command);
	ft_puterr(": `");
	ft_puterr(s);
	ft_puterr("': not a valid identifier\n");
}

void	ft_puterr_env(char *s)
{
	ft_puterr("env: ");
	ft_puterr(s);
	ft_puterr(": No such file or directory\n");
}
