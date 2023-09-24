/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:29:19 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/20 20:12:29 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_puterr(char *s)
{
	ft_putstr_fd(s, STDERR_FILENO);
}

void	ft_puterr_set_status(char *s, t_data *data, int number)
{
	ft_putstr_fd(s, STDERR_FILENO);
	data->exit_status = number;
}

void	ft_puterr_command(char *s, t_data *data)
{
	ft_puterr("minishell: ");
	ft_puterr(s);
	ft_puterr(": command not found\n");
	data->exit_status = 127;
}

void	ft_puterr_permit(char *s)
{
	ft_puterr("minishell: ");
	ft_puterr(s);
	ft_puterr(": Permission denied\n");
}

void	ft_puterr_valid_identifer(char *command, char *s, t_data *data)
{
	ft_puterr("minishell: ");
	ft_puterr(command);
	ft_puterr(": `");
	ft_puterr(s);
	ft_puterr("': not a valid identifier\n");
	data->exit_status = 1;
}
