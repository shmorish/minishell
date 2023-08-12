/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:45:32 by morishitash       #+#    #+#             */
/*   Updated: 2023/07/31 17:39:26 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_string.h"

static size_t	word_counter(const char *s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			counter++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (counter);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	*free_arr(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**append_arr(const char *s, char c, char **array)
{
	size_t	j;
	size_t	k;

	j = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		array[j] = (char *)malloc(sizeof(char) * (word_len(s, c) + 1));
		if (array[j] == NULL)
			return (free_arr(array));
		k = 0;
		while (*s != c && *s != '\0')
			array[j][k++] = *s++;
		array[j++][k] = '\0';
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(const char *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!array)
		return (NULL);
	return (append_arr(s, c, array));
}

// int	main(void)
// {
// 	char	*s;
// 	char	**result;

// 	s = "      split       this for   me  ! ";
// 	result = ft_split(s, ' ');
// 	while (*result != NULL)
// 	{
// 		printf("%s\n", *result);
// 		result++;
// 	}
// }
