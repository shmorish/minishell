/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:27:07 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/10 20:27:41 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_start(char *str, char *charset, int i)
{
	int	j;

	j = 0;
	while (charset[j])
	{
		if (str[i] == charset[j])
			i++;
		j++;
	}
	return (i);
}

static int	check_end(char *str, char *charset, int i)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
			{
				i = i - 1;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (i - 1);
}

static int	word_count(char *str, char *charset)
{
	int	start;
	int	end;
	int	count;
	int	j;
	int	flag;

	start = 0;
	count = 0;
	while (str[start])
	{
		flag = 0;
		j = 0;
		start = check_start(str, charset, start);
		end = check_end(str, charset, start);
		while (charset[j])
		{
			if (str[end] == charset[j])
				flag = 1;
			j++;
		}
		if (flag == 0)
			count++;
		start = end + 1;
	}
	return (count);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	**arr;

	start = 0;
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (word_count(str, charset) + 1));
	while (str[start])
	{
		j = 0;
		start = check_start(str, charset, start);
		end = check_end(str, charset, start);
		arr[i] = (char *)malloc(sizeof(char) * (end - start + 2));
		if (end >= start)
		{
			while (start <= end)
				arr[i][j++] = str[start++];
			arr[i][j] = '\0';
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
