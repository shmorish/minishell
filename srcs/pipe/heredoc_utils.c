/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:42:39 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/11 10:50:41 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rm_heredoc_file(void)
{
	int		i;
	char	*tmp_str;
	char	*new_name;

	i = 0;
	tmp_str = ft_itoa(i);
	new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
	free(tmp_str);
	if (new_name == NULL)
		exit(1);
	while (!access(new_name, F_OK))
	{
		unlink(new_name);
		i++;
		free(new_name);
		tmp_str = ft_itoa(i);
		new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
		free(tmp_str);
		if (new_name == NULL)
			exit(1);
	}
	free(new_name);
}

char	*create_heredoc_file(void)
{
	int		i;
	char	*tmp_str;
	char	*new_name;

	i = 0;
	tmp_str = ft_itoa(i);
	if (tmp_str == NULL)
		return (NULL);
	new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
	free(tmp_str);
	if (new_name == NULL)
		return (NULL);
	while (!access(new_name, F_OK))
	{
		i++;
		free(new_name);
		tmp_str = ft_itoa(i);
		if (tmp_str == NULL)
			return (NULL);
		new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
		free(tmp_str);
		if (new_name == NULL)
			return (NULL);
	}
	return (new_name);
}

void	read_heredoc(char *new_name, char *file_name)
{
	int		fd;
	char	*line;

	while (1)
	{
		fd = open(new_name, O_WRONLY | O_APPEND, 0644);
		ft_printf("> ");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 1)
			;
		else if (!ft_strncmp(line, file_name, ft_strlen(line) - 1))
		{
			close(fd);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		close(fd);
	}
}

void	read_heredoc_expansion(char *new_name, char *file_name)
{
	int		fd;
	char	*line;

	while (1)
	{
		fd = open(new_name, O_WRONLY | O_APPEND, 0644);
		ft_printf("> ");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 1)
			;
		else if (!ft_strncmp(line, file_name, ft_strlen(line) - 1))
		{
			close(fd);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		close(fd);
	}
}

bool	dup2_heredoc(t_file *file, int fd)
{
	if (file->next == NULL)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (false);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		return (false);
	}
	return (true);
}
