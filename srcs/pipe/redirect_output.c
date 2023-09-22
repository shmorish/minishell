/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:00:53 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/22 11:27:13 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	out_file(t_file *file, char *file_name, t_data *data, int *status)
{
	int	fd;

	(void)file;
	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		data->exit_status = 1;
		*status = ERROR;
		return (0);
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_errno(file_name);
		data->exit_status = 1;
		*status = ERROR;
		return (0);
	}
	data->exit_status = 0;
	return (fd);
}

int	append(t_file *file, char *file_name, t_data *data, int *status)
{
	int	fd;

	(void)file;
	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		data->exit_status = 1;
		*status = ERROR;
		return (0);
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_errno(file_name);
		data->exit_status = 1;
		*status = ERROR;
		return (0);
	}
	data->exit_status = 0;
	return (fd);
}
