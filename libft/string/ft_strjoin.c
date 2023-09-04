/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 12:06:35 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/04 20:11:09 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_string.h"

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*ret;
// 	size_t	len;

// 	if (!s1 || !s2)
// 		return (0);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	ret = malloc(sizeof(char) * (len + 1));
// 	if (!ret)
// 		return (0);
// 	ft_strlcpy(ret, s1, len + 1);
// 	ft_strlcat(ret, s2, len + 1);
// 	return (ret);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ans = (char *)malloc(sizeof(char) * len);
	if (!ans)
		return (NULL);
	*ans = '\0';
	ft_strlcat(ans, s1, ft_strlen(s1) + 1);
	ft_strlcat(ans, s2, len);
	return (ans);
}