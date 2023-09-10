/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:20:06 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 17:20:06 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_echo_no_option(char **array, size_t count)
{
	while (array[count])
	{
		ft_printf("%s", array[count]);
		if (count != ft_get_list_size(array) - 1)
			ft_printf(" ");
		count++;
	}
	ft_printf("\n");
}

static void	ft_echo_option(char **array, size_t count)
{
	size_t	i;

	while (array[count] != NULL && !ft_strncmp("-n", array[count], 2))
	{
		i = 2;
		while (array[count][i] == 'n')
			i++;
		if (array[count][i] != '\0')
		{
			ft_echo_no_option(array, count);
			return ;
		}
		count++;
	}
	if (array[count] == NULL)
		return ;
	while (array[count])
	{
		ft_printf("%s", array[count]);
		if (count != ft_get_list_size(array) - 1)
			ft_printf(" ");
		count++;
	}
}

void	ft_echo(char **array, t_data *data)
{
	size_t	count;

	count = 1;
	if (array[count] != NULL && !ft_strncmp("-n", array[count], 2))
	{
		ft_echo_option(array, count);
		data->exit_status = 0;
	}
	else
	{
		ft_echo_no_option(array, count);
		data->exit_status = 0;
	}
}
