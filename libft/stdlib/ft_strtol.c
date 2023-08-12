/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 20:20:08 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/09 17:21:59 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ctype.h"

static long	isoverflow(long n, int d, int sign)
{
	if (n * sign > LONG_MAX / 10 || (n * sign == LONG_MAX / 10 && d > LONG_MAX
			% 10))
		return (1);
	if (n * sign < LONG_MIN / 10 || (n * sign == LONG_MIN / 10 && d > -1
			* (LONG_MIN % 10)))
		return (-1);
	return (0);
}

long	ft_strtol(const char *str)
{
	long	n;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	n = 0;
	while (ft_isdigit(*str))
	{
		if (isoverflow(n, *str - '0', sign) == 1)
			return (LONG_MAX);
		else if (isoverflow(n, *str - '0', sign) == -1)
			return (LONG_MIN);
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (n * sign);
}
