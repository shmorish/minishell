/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbinary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 19:52:27 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/18 19:58:02 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putbinary(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb >= 2)
		len += ft_putbinary(nb / 2);
	len += ft_putchar(nb % 2 + '0');
	return (len);
}
