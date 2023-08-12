/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:40:16 by morishitash       #+#    #+#             */
/*   Updated: 2023/06/10 23:31:30 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= 16;
		len++;
	}
	return (len);
}

int	ft_lower_puthex(unsigned int nb)
{
	unsigned int	n;

	n = nb;
	if (nb > 15)
	{
		ft_lower_puthex(nb / 16);
		nb %= 16;
	}
	if (nb < 10)
		ft_putchar(nb + '0');
	if (nb >= 10)
		ft_putchar(nb - 10 + 'a');
	return (hex_len(n));
}

int	ft_upper_puthex(unsigned int nb)
{
	unsigned int	n;

	n = nb;
	if (nb > 15)
	{
		ft_upper_puthex(nb / 16);
		nb %= 16;
	}
	if (nb < 10)
		ft_putchar(nb + '0');
	if (nb >= 10)
		ft_putchar(nb - 10 + 'A');
	return (hex_len(n));
}
