/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:59:16 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/18 19:58:16 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		result_length;
	va_list	args;

	i = 0;
	result_length = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			result_length += ft_format(&args, str[i + 1]);
			i++;
		}
		else
			result_length += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (result_length);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int	a;
// 	int	b;
// 	char *str1 = "Hello, world!";
// 	char *str2 = "Konnichiwa, sekai!";

// 	a = printf("%s %s\n", str1, str2);
// 	b = ft_printf("%b\n", a);

// 	printf("printf: %d\n", a);
// 	ft_printf("ft_printf: %d\n", b);
// }
