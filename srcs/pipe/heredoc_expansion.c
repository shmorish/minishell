/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:38:04 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/14 11:51:43 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc_join(char *before_l, char *after_l, char *envstr, size_t *i)
{
	char	*newline;
	char	*delete_line;

	newline = ft_strjoin(before_l, envstr);
	if (newline == NULL)
		return (expansion_free(before_l, after_l, envstr), NULL);
	delete_line = newline;
	newline = ft_strjoin(newline, after_l);
	free(delete_line);
	if (newline == NULL)
		return (expansion_free(before_l, after_l, envstr), NULL);
	*i = ft_strlen(before_l) + ft_strlen(envstr);
	expansion_free(before_l, after_l, envstr);
	return (newline);
}

char	*heredoc_newline(char *line, size_t *i, t_data *data)
{
	size_t	j;
	char	*before_line;
	char	*after_line;
	char	*env_str;
	char	*env_name;

	j = 0;
	before_line = ft_substr(line, 0, *i - 1);
	while (ft_isalnum(line[*i + j]) || line[*i + j] == '_')
		j++;
	after_line = ft_substr(line, *i + j, ft_strlen(line) - (*i + j));
	if (after_line == NULL)
		return (NULL);
	env_name = ft_substr(line, *i, j);
	env_str = ft_strdup(get_env_val(data->env_head, env_name));
	free(env_name);
	if (env_str == NULL)
		env_str = ft_strdup("");
	free(line);
	return (heredoc_join(before_line, after_line, env_str, i));
}

char	*heredoc_expansion(char *line, t_data *data)
{
	size_t	index;
	char	*newline;

	index = 0;
	newline = ft_strdup(line);
	free(line);
	while (newline[index])
	{
		if (newline[index++] == '$')
		{
			if (newline[index] == '\0')
				break ;
			else if (newline[index] == '$')
				;
			else
			{
				newline = heredoc_newline(newline, &index, data);
				if (newline == NULL)
					return (NULL);
			}
		}
	}
	return (newline);
}

void	read_heredoc(char *new_name, char *file_name, t_data *data)
{
	int		fd;
	char	*line;

	while (1)
	{
		fd = open(new_name, O_WRONLY | O_APPEND, 0644);
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strlen(file_name) == 0 && ft_strlen(line) == 0)
		{
			free_and_close(line, fd);
			break ;
		}
		else if (ft_strlen(line)
			&& !ft_strncmp(line, file_name, ft_strlen(line)))
		{
			free_and_close(line, fd);
			break ;
		}
		write_heredoc(fd, line, data);
		close(fd);
	}
}

void	free_and_close(char *line, int fd)
{
	free(line);
	close(fd);
}
