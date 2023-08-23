/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:01:20 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/23 18:23:39 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strccpy(char *str, char c)
{
	unsigned int	i;
	char			*ans;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	ans = (char *)malloc(sizeof(char) * (i + 1));
	if (ans == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		ans[i] = str[i];
		i++;
	}
	ans[i] = '\0';
	free(str);
	return (ans);
}
