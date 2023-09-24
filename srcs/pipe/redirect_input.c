/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/22 11:27:25 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	in_file(t_file *file, char *file_name, t_data *data, int *status)
{
	int	fd;

	(void)data;
	(void)file;
	if (file_name[0] == '\0')
	{
		ft_puterr("minishell: ambiguous redirect\n");
		data->exit_status = 1;
		*status = ERROR;
		return (0);
	}
	fd = open(file_name, O_RDONLY);
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
