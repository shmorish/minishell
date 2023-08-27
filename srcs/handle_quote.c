/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:00:32 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/27 18:43:06 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define PROCESS_ID 4242

int	ft_is_env(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*puterr_null_return(void)
{
	ft_puterr("Error: quote is not closed.\n");
	return (NULL);
}

void	handle_single_quote(char *newline, int *i)
{
	int	j;

	j = 0;
	*i = *i + 1;
	while (newline[*i + j] != '\0')
	{
		if (newline[*i + j] == '\'')
			break ;
		j++;
	}
	*i = *i + j;
}

char	*convert_process_id(char *newline, int *i)
{
	char	*before_line;
	char	*after_line;
	char	*convert_env;

	before_line = ft_substr(newline, 0, *i - 1);
	after_line = ft_substr(newline, *i + 1, ft_strlen(newline) - (*i + 1));
	convert_env = ft_itoa(PROCESS_ID);
	// convert_env = ft_itoa(getpid());
	if (convert_env == NULL || after_line == NULL || before_line == NULL)
		return (NULL);
	newline = ft_strjoin(before_line, convert_env);
	newline = ft_strjoin(newline, after_line);
	free(before_line);
	free(after_line);
	free(convert_env);
	*i = ft_strlen(before_line) + ft_strlen(convert_env);
	return (newline);
}

char	*convert_env_to_newline(char *newline, t_env *env_head, char *env_line, char *before_line, char *after_line)
{
	char	*convert_env;

	convert_env = ft_strdup(get_env_var(env_head, env_line));
	if (convert_env == NULL)
		return (NULL);
	newline = ft_strjoin(before_line, convert_env);
	newline = ft_strjoin(newline, after_line);
	return (newline);

	// convert_env = ft_strdup(get_env_var(env_head, env_line));
	// if (convert_env == NULL || before_line == NULL || after_line == NULL)
	// 	return (NULL);
	// newline = ft_strjoin(before_line, convert_env);
	// newline = ft_strjoin(newline, after_line);
	// free(before_line);
	// free(after_line);
	// free(env_line);
	// free(convert_env);
	// i = ft_strlen(before_line) + ft_strlen(convert_env);
}

char	*handle_quote(char *line, t_env *env_head)
{
	char	*newline;
	char	*before_line;
	char	*after_line;
	char	*convert_env;
	char	*env_line;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	newline = ft_strdup(line);
	while (newline[i] != '\0')
	{
		if (newline[i] == '\'')
		{
			handle_single_quote(newline, &i);
			if (newline[i] == '\0')
				return (puterr_null_return());
		}
		else if (newline[i] == '\"')
		{
			newline[i] = '\'';
			i++;
			while (newline[i] != '\0')
			{
				if (newline[i] == '\"')
					break ;
				if (newline[i] == '$')
				{
					j = 0;
					before_line = ft_substr(newline, 0, i);
					if (before_line == NULL)
						return (NULL);
					i++;
					while (ft_is_env(newline[i + j]))
						j++;
					if (newline[i] == '$')
					{
						newline = convert_process_id(newline, &i);
						if (newline == NULL)
							return (NULL);
					}
					else if (j == 0)
					{
						free(before_line);
						continue ;
					}
					else
					{
						after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
						env_line = ft_substr(newline, i, j);
						if (after_line == NULL || env_line == NULL)
							return (NULL);
						if (get_env_var(env_head, env_line) == NULL)
						{
							newline = ft_strjoin(before_line, after_line);
							i = i - 2;
						}
						else
						{
							// newline = convert_env_to_newline(newline, env_head, env_line, before_line, after_line);
							convert_env = ft_strdup(get_env_var(env_head, env_line));
							if (convert_env == NULL)
								return (NULL);
							newline = ft_strjoin(before_line, convert_env);
							newline = ft_strjoin(newline, after_line);
							free(before_line);
							free(after_line);
							free(env_line);
							free(convert_env);
							i = ft_strlen(before_line) + ft_strlen(convert_env);
						}
					}
				}
				i++;
			}
			if (newline[i] == '\0')
				return (puterr_null_return());
			newline[i] = '\'';
			i++;
		}
		else
		{
			if (newline[i] == '$')
			{
				j = 0;
				before_line = ft_substr(newline, 0, i);
				i++;
				while (ft_is_env(newline[i + j]))
					j++;
				if (newline[i] == '$')
				{
					tmp = ft_itoa(PROCESS_ID);
					// tmp = ft_itoa(getpid());
					convert_env = ft_strdup(tmp);
					free(tmp);
					after_line = ft_substr(newline, i + 1, ft_strlen(newline) - (i + 1));
					if (convert_env == NULL || before_line == NULL || after_line == NULL)
						return (NULL);
					newline = ft_strjoin(before_line, convert_env);
					newline = ft_strjoin(newline, after_line);
					free(before_line);
					free(after_line);
					free(convert_env);
					i = ft_strlen(before_line) + ft_strlen(convert_env);
				}
				else if (j == 0)
				{
					free(before_line);
					continue ;
				}
				else
				{
					after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
					env_line = ft_substr(newline, i, j);
					if (get_env_var(env_head, env_line) == NULL)
					{
						newline = ft_strjoin(before_line, after_line);
						i = i - 2;
					}
					else
					{
						convert_env = ft_strdup(get_env_var(env_head, env_line)); // segmantation fault
						if (convert_env == NULL || before_line == NULL || after_line == NULL)
							return (NULL);
						newline = ft_strjoin(before_line, convert_env);
						newline = ft_strjoin(newline, after_line);
						free(before_line);
						free(after_line);
						free(env_line);
						free(convert_env);
						i = ft_strlen(before_line) + ft_strlen(convert_env);
					}
				}
			}
		}
		i++;
	}
	return (newline);
}

