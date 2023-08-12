/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:20:05 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/18 19:50:42 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list *data, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(*data, int));
	if (format == 's')
		len += ft_putstr(va_arg(*data, char *));
	if (format == 'p')
		len += ft_putptr(va_arg(*data, uintptr_t));
	if (format == 'd')
		len += ft_putnbr(va_arg(*data, int));
	if (format == 'i')
		len += ft_putnbr(va_arg(*data, int));
	if (format == 'u')
		len += ft_putunbr(va_arg(*data, unsigned int));
	if (format == 'x')
		len += ft_lower_puthex(va_arg(*data, unsigned int));
	if (format == 'X')
		len += ft_upper_puthex(va_arg(*data, unsigned int));
	if (format == 'b')
		len += ft_putbinary(va_arg(*data, unsigned int));
	if (format == '%')
		len += write(STDOUT_FILENO, "%", 1);
	return (len);
}
