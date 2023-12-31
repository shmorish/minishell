/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_once.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 13:45:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/04 12:34:00 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static size_t	skip_delimiter(char *str, char c, size_t arr_len)
{
	size_t	i;

	i = 0;
	if (arr_len == 1)
	{
		while (str[i] && str[i] != c)
			i++;
	}
	else
	{
		while (str[i])
			i++;
	}
	return (i);
}

static char	**do_split_once(char **array, char *str, char c, size_t arr_len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < 2 && *str && arr_len--)
	{
		i = skip_delimiter(str, c, arr_len);
		array[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!array[j])
		{
			free_all_split_once(array, j);
			return (NULL);
		}
		ft_strlcpy(array[j], str, (i + 1));
		j++;
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
	if (!do_split_once(array, str, c, 2))
		return (NULL);
	return (array);
}
