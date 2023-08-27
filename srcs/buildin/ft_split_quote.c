/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 11:50:53 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/27 15:28:04 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_quote(char *str)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	while (str[index])
	{
		if (str[index] == '\'')
			count++;
		index++;
	}
	return (count);
}
static size_t	count_word(char *str, char c)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;

	while (str[index])
	{
		while (str[index] == c)
			index++;
		if (str[index] == '\0')
			break ;
		if (str[index] != '\'')
		{
			while (str[index] && str[index] != c)
				index++;
		}
		else
		{
			index++;
			while (str[index] && str[index] != '\'')
				index++;
			while (str[index])
			{
				if (str[index] == '\'' && (str[index + 1] == ' ' || !str[index + 1]))
					break ;
				index++;
			}
			index++;
		}
		count++;
	}
	return (count);
}

static void	free_all_split_quote(char **array, size_t len)
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

static char	**do_split_quote(char **array, char *str, char c, size_t arr_len)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (*str && arr_len--)
	{
		while (*str == c)
			str++;
		i = 0;
		if (str[i] != '\'')
		{
			while (str[i] && str[i] != c)
				i++;
		}
		else
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			while (str[i])
			{
				if (str[i] == '\'' && (str[i + 1] == ' ' || !str[i + 1]))
					break ;
				i++;
			}
		}
		array[j] = (char *)malloc(sizeof(char) * (i + 1));
		if (!array[j])
		{
			free_all_split_quote(array, j);
			return (NULL);
		}
		ft_strlcpy(array[j++], str, (i + 1));
		str += i;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split_quote(char const *s, char c)
{
	char	**array;
	char	*str;
	size_t	arr_len;

	str = (char *)s;
	if (count_quote(str) == 0)
		return (ft_split(s, c));
	arr_len = count_word(str, c);
	ft_printf("%ld\n", arr_len);
	array = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!array)
		return (NULL);
	if (!do_split_quote(array, str, c, arr_len))
		return (NULL);
	return (array);
}