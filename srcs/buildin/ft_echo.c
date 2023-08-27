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

static void	check_quote(char **list, size_t count)
{
	size_t	i;
	char	*str;

	i = 0;
	while (list[count][i] != '\0' && list[count][i] != '\'')
		i++;
	if (list[count][i] == '\'')
	{
		str = list[count];
		list[count] = ft_strtrim(str, "'");
		free(str);
	}
}

static void	ft_echo_no_option(char **list, size_t count)
{
	while (list[count])
	{
		check_quote(list, count);
		ft_printf("%s", list[count]);
		if (count != ft_get_list_size(list) - 1)
			ft_printf(" ");
		count++;
	}
	ft_printf("\n");
}

static void	ft_echo_option(char **list, size_t count)
{
	size_t	i;

	while (list[count] != NULL && !ft_strncmp("-n", list[count], 2))
	{
		i = 2;
		while (list[count][i] == 'n')
			i++;
		if (list[count][i] != '\0')
		{
			ft_echo_no_option(list, count);
			return ;
		}
		count++;
	}
	if (list[count] == NULL)
		return ;
	while (list[count])
	{
		check_quote(list, count);
		ft_printf("%s", list[count]);
		if (count != ft_get_list_size(list) - 1)
			ft_printf(" ");
		count++;
	}
}

void	ft_echo(char **list)
{
	size_t	count;

	count = 1;
	if (list[count] != NULL && !ft_strncmp("-n", list[count], 2))
		ft_echo_option(list, count);
	else
		ft_echo_no_option(list, count);
}
