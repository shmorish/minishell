/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:54:18 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/31 17:37:19 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ctype.h"

int	ft_isdouble(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '.')
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == '.' && dot_count == 0)
				dot_count++;
			else
				return (1);
		}
		i++;
	}
	if (str[i - 1] == '.')
		return (1);
	return (0);
}

// # include <stdio.h>
// int	main(void)
// {
// 	char	*str;

// 	str = "123456";
// 	printf("%d\n", ft_isdouble(str));
// 	return (0);
// }
