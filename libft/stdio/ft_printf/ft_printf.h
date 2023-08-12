/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 14:03:09 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/18 19:52:07 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include <inttypes.h>

int	ft_printf(const char *str, ...);
int	ft_format(va_list *data, const char format);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putptr(uintptr_t nb);
int	ft_putnbr(int nb);
int	ft_putunbr(unsigned int nb);
int	ft_lower_puthex(unsigned int nb);
int	ft_upper_puthex(unsigned int nb);
int	ft_putbinary(unsigned int nb);

#endif