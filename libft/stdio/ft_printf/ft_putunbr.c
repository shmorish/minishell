/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:01:35 by morishitash       #+#    #+#             */
/*   Updated: 2023/06/10 17:56:48 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	unbr_len(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_putunbr(unsigned int nb)
{
	unsigned int	n;

	n = nb;
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		nb %= 10;
	}
	if (nb < 10)
		ft_putchar(nb + '0');
	return (unbr_len(n));
}
