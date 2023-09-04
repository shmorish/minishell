/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 04:10:05 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/04 20:24:23 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ans;
	size_t	i;
	size_t	tail;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	tail = ft_strlen(s1);
	while (tail > i && ft_strchr(set, s1[tail - 1]))
		tail--;
	ans = (char *)malloc(sizeof(char) * (tail - i + 1));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, &s1[i], (tail - i + 1));
	return (ans);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char s[] = "   a a a 3127890 a aaa  ";
// 	printf("%s\n", ft_strtrim(s, " a"));
// }