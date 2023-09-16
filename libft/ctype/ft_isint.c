/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:35:42 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/16 14:48:09 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ctype.h"
#include "../includes/ft_stdlib.h"
#include "../includes/ft_string.h"

// check that the string is a valid integer
// return 1 if valid, 0 if not
int	ft_isint(char *str)
{
	long	num;
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	if (ft_strlen(str) > 11)
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	num = ft_strtol(str);
	if (num < INT_MIN || INT_MAX < num)
		return (0);
	return (1);
}
