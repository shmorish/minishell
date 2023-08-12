/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:38:59 by shmorish          #+#    #+#             */
/*   Updated: 2023/07/31 17:41:41 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	if (*s == '\0' && c == 0)
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == (char)c)
			tmp = (char *)s;
		s++;
		if (*s == '\0' && c == 0)
			return ((char *)s);
	}
	return (tmp);
}
