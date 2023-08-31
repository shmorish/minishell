/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 21:00:32 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/31 16:55:44 by ryhara           ###   ########.fr       */
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

void	free_fourline(char *line1, char *line2, char *line3, char *line4)
{
	free(line1);
	free(line2);
	free(line3);
	free(line4);
}

char	*handle_processid_exitstatus(char *newline, char *before_line, int *i,
		t_data *data)
{
	char	*env_line;
	char	*after_line;
	char	*tmp;

	if (newline[*i] == '$')
		env_line = ft_strdup("$$");
		// env_line = ft_itoa(PROCESS_ID);
	else
		env_line = ft_itoa(data->exit_status);
	printf("env_line: %s\n", env_line);
	after_line = ft_substr(newline, *i + 1, ft_strlen(newline) - (*i + 1));
	if (env_line == NULL || after_line == NULL)
		return (NULL);
	tmp = ft_strjoin_three(before_line, env_line, after_line);
	if (tmp == NULL)
		return (NULL);
	*i = ft_strlen(before_line) + ft_strlen(env_line) - 1;
	free(after_line);
	free(env_line);
	free(newline);
	newline = tmp;
	return (tmp);
}

char	*handle_env(char *newline, int *i, int *j, t_env *env_head)
{
	char	*env_line;
	char	*env_value;

	env_line = ft_substr(newline, *i, *j);
	if (get_env_val(env_head, env_line) == NULL)
		env_value = ft_strdup("");
	else
		env_value = ft_strdup(get_env_val(env_head, env_line));
	if (env_line == NULL || env_value == NULL)
		return (NULL);
	free(env_line);
	return (env_value);
}

char	*handle_quote(char *line, t_env *env_head, t_data *data)
{
	char	*newline;
	char	*before_line;
	char	*after_line;
	char	*env_value;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	newline = ft_strdup(line);
	while (newline[i] != '\0')
	{
		if (newline[i] == '\'')
			handle_single_quote(newline, &i);
		else if (newline[i] == '\"')
		{
			i++;
			if (newline[i] == '\"')
				continue ;
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
					newline = handle_processid_exitstatus(newline, before_line, &i, data);
					free(before_line);
				}
				else if (j == 0)
				{
					free(before_line);
					continue ;
				}
				else
				{
					env_value = handle_env(newline, &i, &j, env_head);
					after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
					if (after_line == NULL || env_value == NULL)
						return (NULL);
					tmp = ft_strjoin_three(before_line, env_value, after_line);
					if (tmp == NULL)
						return (NULL);
					free(newline);
					newline = tmp;
					i = ft_strlen(before_line) + ft_strlen(env_value) - 1;
					free(before_line);
					free(after_line);
					free(env_value);
				}
			}
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
					newline = handle_processid_exitstatus(newline, before_line, &i, data);
					free(before_line);
				}
				else if (j == 0)
				{
					free(before_line);
					continue ;
				}
				else
				{
					env_value = handle_env(newline, &i, &j, env_head);
					after_line = ft_substr(newline, i + j, ft_strlen(newline) - (i + j));
					if (after_line == NULL || env_value == NULL)
						return (NULL);
					tmp = ft_strjoin_three(before_line, env_value, after_line);
					if (tmp == NULL)
						return (NULL);
					free(newline);
					newline = tmp;
					i = ft_strlen(before_line) + ft_strlen(env_value) - 1;
					free(before_line);
					free(after_line);
					free(env_value);
				}
			}
		}
		i++;
	}
	return (newline);
}
