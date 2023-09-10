/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_long_overflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:15:56 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/31 15:15:58 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	is_long_overflow(const char *str)
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
			return (true);
		else if (isoverflow(n, *str - '0', sign) == -1)
			return (true);
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (false);
}
