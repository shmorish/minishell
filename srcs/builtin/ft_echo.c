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

static void	ft_echo_option(char **list, size_t count)
{
	size_t	i;

	while (!ft_strncmp("-n", list[count], 2))
	{
		i = 2;
		while (list[count][i] == 'n')
			i++;
		if (list[count][i] != '\0')
			break ;
		count++;
	}
	if (list[count] == NULL)
		return ;
	while (list[count])
	{
		printf("%s", list[count]);
		if (count != ft_get_list_size(list) - 1)
			printf(" ");
		count++;
	}
}

static void	ft_echo_no_option(char **list, size_t count)
{
	while (list[count])
	{
		printf("%s", list[count]);
		if (count != ft_get_list_size(list) - 1)
			printf(" ");
		count++;
	}
	printf("\n");
}

// static size_t	check_doller(char *str)
// {

// }

// static void	ft_put_doller(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '$')
// 		{

// 		}
// 		write(STDOUT_FILENO, str, 1);
// 	}
// }
void	ft_echo(char **list)
{
	size_t	count;

	count = 1;
	if (!ft_strncmp("-n", list[count], 2))
		ft_echo_option(list, count);
	else
		ft_echo_no_option(list, count);
}
