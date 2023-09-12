/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:27:07 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/12 12:48:44 by ryhara           ###   ########.fr       */
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
		{
			i++;
			j = 0;
		}
		else
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
	int		start;
	int		end;
	char	**arr;

	start = 0;
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (word_count(str, charset) + 1));
	if (arr == NULL)
		return (NULL);
	while (str[start])
	{
		start = check_start(str, charset, start);
		end = check_end(str, charset, start);
		if (end >= start)
		{
			arr[i] = ft_substr(str, start, end - start + 1);
			if (arr[i++] == NULL)
				return (free_char_array(arr), NULL);
			start = end + 1;
		}
	}
	arr[i] = NULL;
	return (arr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *str;
// 	char *charset;
// 	char **ans;
// 	int i;
// 	int count;

// 	str = "_he_l+lo__+__wo+r+ld__+__japan_,_+__42__+_,_42Tok,yo_";
// 	charset = "+_,";
// 	i = 0;
// 	count = (word_count(str, charset) + 1);
// 	printf("count : %d\n", count);
// 	ans = ft_split_charset(str, charset);
// 	while (i < count)
// 	{
// 		printf("%d: %s\n", i, ans[i]);
// 		i++;
// 	}
// }