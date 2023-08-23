/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:00:32 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/23 18:17:31 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_env(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*handle_quote(char *line, t_env *env_head)
{
	char	*newline;
	char	*before_line;
	char	*after_line;
	char	*convert_env;
	int		i;
	int		j;

	i = 0;
	newline = ft_strdup(line); //___ばつ
	while (newline[i] != '\0')
	{
		if (newline[i] == '\'')
		{
			i++;
			while (newline[i] != '\0')
			{
				if (newline[i] == '\'')
					break ;
				i++;
			}
			if (newline[i] == '\0')
			{
				ft_puterr("Error: quote is not closed.");
				return (NULL);
			}
		}
		if (newline[i] == '\"')
		{
			newline[i] = '\'';
			i++;
			while (newline[i] != '\0')
			{
				// printf("newline[i]: %c\n", newline[i]); //___ばつ
				// printf("newline: %s\n", newline);
				if (newline[i] == '\"')
					break ;
				if (newline[i] == '$')
				{
					j = 0;
					before_line = ft_substr(newline, 0, i);
					i++;
					while (ft_is_env(newline[i + j]))
						j++;
					after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
					convert_env = ft_strdup(get_env_var(env_head, ft_substr(newline, i, j)));
					if (convert_env == NULL)
						return (NULL);
					newline = ft_strjoin(before_line, convert_env);
					newline = ft_strjoin(newline, after_line);
					free(before_line);
					free(after_line);
					free(convert_env);
					i = ft_strlen(before_line) + ft_strlen(convert_env);
				}
				i++;
			}
			if (newline[i] == '\0')
			{
				ft_puterr("Error: quote is not closed.");
				return (NULL);
			}
			newline[i] = '\'';
			i++;
		}
		i++;
	}
	return (newline);
}
