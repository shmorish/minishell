/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:00:32 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/31 16:34:56 by ryhara           ###   ########.fr       */
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

	convert_env = ft_strdup(get_env_val(env_head, env_line));
	if (convert_env == NULL)
		return (NULL);
	newline = ft_strjoin(before_line, convert_env);
	newline = ft_strjoin(newline, after_line);
	return (newline);

	// convert_env = ft_strdup(get_env_val(env_head, env_line));
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

char	*ft_strjoin_three(char *str1, char *str2, char *str3)
{
	int		strlen1;
	int		strlen2;
	int		strlen3;
	char	*newstr;

	if (str1 == NULL)
		strlen1 = 0;
	else
		strlen1 = ft_strlen(str1);
	if (str2 == NULL)
		strlen2 = 0;
	else
		strlen2 = ft_strlen(str2);
	if (str3 == NULL)
		strlen3 = 0;
	else
		strlen3 = ft_strlen(str3);
	newstr = (char *)malloc(sizeof(char) * (strlen1 + strlen2 + strlen3 + 1));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, str1, strlen1 + 1);
	ft_strlcpy(newstr + strlen1, str2, strlen2 + 1);
	ft_strlcpy(newstr + strlen1 + strlen2, str3, strlen3 + 1);
	return (newstr);
}

char	*handle_quote(char *line, t_env *env_head, t_data *data)
{
	char	*newline;
	char	*before_line;
	char	*after_line;
	// char	*convert_env;
	char	*env_value;
	char	*env_line;
	char	*tmp;
	int		i;
	int		j;

	(void)env_head;
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
					if (newline[i] == '$' || newline[i] == '?')
					{
						if (newline[i] == '$')
							env_line = ft_strdup("$$");
						else
							env_line = ft_itoa(data->exit_status);
						after_line = ft_substr(newline, i + 1, ft_strlen(newline) - (i + 1));
						printf("after_line :[%s]\n", after_line);
						if (env_line == NULL || after_line == NULL)
							return (NULL);
						tmp = ft_strjoin_three(before_line, env_line, after_line);
						if (tmp == NULL)
							return (NULL);
						i = ft_strlen(before_line) + ft_strlen(env_line) - 1;
						// printf("before_line :[%s]\n", before_line);
						// printf("env_line :[%s]\n", env_line);
						free(newline);
						free(before_line);
						free(after_line);
						free(env_line);
						newline = tmp;
						// printf("i :[%d]\n", i);
						// printf("newline :[%s]\n", newline);
						// printf("newline[i] :[%c]\n", newline[i]);
					}
					else if (j == 0)
					{
						free(before_line);
						continue ;
					}
					else
					{
						env_line = ft_substr(newline, i, j);
						// printf("env_line :[%s]\n", env_line);
						env_value = ft_strdup(get_env_val(env_head, env_line));
						// printf("env_value :[%s]\n", env_value);
						after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
						// printf("after_line :[%s]\n", after_line);
						if (env_line == NULL || after_line == NULL || env_value == NULL)
							return (NULL);
						tmp = ft_strjoin_three(before_line, env_value, after_line);
						if (tmp == NULL)
							return (NULL);
						free(newline);
						newline = tmp;
						i = ft_strlen(before_line) + ft_strlen(env_value) - 1;
						printf("before_line :[%s]\n", before_line);
						printf("env_value :[%s]\n", env_value);
						printf("after_line :[%s]\n", after_line);
						printf("i :[%d]\n", i);
						printf("newline :[%s]\n", newline);
						printf("newline[i] :[%c]\n", newline[i]);
						free(before_line);
						free(after_line);
						free(env_line);
						free(env_value);
					}
				}
				i++;
			}
			if (newline[i] == '\0')
				return (puterr_null_return());
			i++;
		}
		else
		{
			if (newline[i] == '$')
			{
				j = 0;
				before_line = ft_substr(newline, 0, i);
				if (before_line == NULL)
					return (NULL);
				i++;
				while (ft_is_env(newline[i + j]))
					j++;
				if (newline[i] == '$' || newline[i] == '?')
				{
						// env_line = ft_itoa(PROCESS_ID);
					if (newline[i] == '$')
						env_line = ft_strdup("$$");
					else
						env_line = ft_itoa(data->exit_status);
					after_line = ft_substr(newline, i + 1, ft_strlen(newline) - (i + 1));
					printf("after_line :[%s]\n", after_line);
					if (env_line == NULL || after_line == NULL)
						return (NULL);
					tmp = ft_strjoin_three(before_line, env_line, after_line);
					if (tmp == NULL)
						return (NULL);
					i = ft_strlen(before_line) + ft_strlen(env_line) - 1;
					// printf("before_line :[%s]\n", before_line);
					// printf("env_line :[%s]\n", env_line);
					free(newline);
					free(before_line);
					free(after_line);
					free(env_line);
					newline = tmp;
					// printf("i :[%d]\n", i);
					// printf("newline :[%s]\n", newline);
					// printf("newline[i] :[%c]\n", newline[i]);
				}
				else if (j == 0)
				{
					free(before_line);
					continue ;
				}
				else
				{
					env_line = ft_substr(newline, i, j);
					// printf("env_line :[%s]\n", env_line);
					env_value = ft_strdup(get_env_val(env_head, env_line));
					// printf("env_value :[%s]\n", env_value);
					after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
					// printf("after_line :[%s]\n", after_line);
					if (env_line == NULL || after_line == NULL || env_value == NULL)
						return (NULL);
					tmp = ft_strjoin_three(before_line, env_value, after_line);
					if (tmp == NULL)
						return (NULL);
					free(newline);
					newline = tmp;
					i = ft_strlen(before_line) + ft_strlen(env_value) - 1;
					printf("before_line :[%s]\n", before_line);
					printf("env_value :[%s]\n", env_value);
					printf("after_line :[%s]\n", after_line);
					printf("i :[%d]\n", i);
					printf("newline :[%s]\n", newline);
					printf("newline[i] :[%c]\n", newline[i]);
					free(before_line);
					free(after_line);
					free(env_line);
					free(env_value);
				}
			}
		}
		i++;
	}
	return (newline);
}
