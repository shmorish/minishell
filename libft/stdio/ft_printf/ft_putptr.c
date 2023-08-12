/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 11:35:46 by morishitash       #+#    #+#             */
/*   Updated: 2023/06/10 23:56:20 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ptr_len(uintptr_t nb)
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

static int	ft_puthex(uintptr_t nb)
{
	uintptr_t	n;

	n = nb;
	if (nb > 15)
	{
		ft_puthex(nb / 16);
		nb %= 16;
	}
	if (nb < 10)
		ft_putchar(nb + '0');
	if (nb >= 10)
		ft_putchar(nb - 10 + 'a');
	return (ptr_len(n));
}

int	ft_putptr(uintptr_t nb)
{
	if (nb == 0)
		return (write(STDOUT_FILENO, "0x0", 3));
	write(STDOUT_FILENO, "0x", 2);
	ft_puthex(nb);
	return (ptr_len(nb) + 2);
}
