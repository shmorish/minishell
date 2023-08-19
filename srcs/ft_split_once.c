/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:45:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/19 16:03:55 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_all_split_once(char **array, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**do_split(char **array, char *str, char c, size_t arr_len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*str && arr_len--)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		array[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!array[j])
		{
			free_all_split_once(array, j);
			return (NULL);
		}
		ft_strlcpy(array[j++], str, (i + 1));
		str += (i + 1);
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split_once(char const *s, char c)
{
	char	**array;
	char	*str;

	str = (char *)s;
	array = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!array)
		return (NULL);
	if (!do_split(array, str, c, 2))
		return (NULL);
	return (array);
}
