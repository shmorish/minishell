/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 12:58:07 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/10 23:17:32 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define HEREDOC_FILE ".heredoc"

void	rm_heredoc_file(void)
{
	int	i;
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

void	heredoc(t_file *file, char *file_name)
{
	int	fd;
	int	i;
	char	*tmp_str;
	char	*new_name;
	char	*line;

	i = 0;
	tmp_str = ft_itoa(i);
	new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
	free(tmp_str);
	if (new_name == NULL)
		exit(1);
	while (!access(new_name, F_OK))
	{
		i++;
		free(new_name);
		tmp_str = ft_itoa(i);
		new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
		free(tmp_str);
		if (new_name == NULL)
			exit(1);
	}
	fd = open(new_name, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		free(new_name);
		exit(1);
	}
	close(fd);
	while (1)
	{
		fd = open(new_name, O_WRONLY | O_APPEND, 0644);
		ft_printf("> ");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, file_name, ft_strlen(line) - 1))
		{
			close(fd);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		close(fd);
	}
	fd = open(new_name, O_RDONLY);
	free(new_name);
	if (file->next == NULL)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	quote_heredoc(t_file *file, char *file_name)
{
	int	fd;
	int	i;
	char	*tmp_str;
	char	*new_name;
	char	*line;

	i = 0;
	tmp_str = ft_itoa(i);
	new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
	free(tmp_str);
	if (new_name == NULL)
		exit(1);
	while (!access(new_name, F_OK))
	{
		i++;
		free(new_name);
		tmp_str = ft_itoa(i);
		new_name = ft_strjoin(HEREDOC_FILE, tmp_str);
		free(tmp_str);
		if (new_name == NULL)
			exit(1);
	}
	fd = open(new_name, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		free(new_name);
		exit(1);
	}
	close(fd);
	while (1)
	{
		fd = open(new_name, O_WRONLY | O_APPEND, 0644);
		ft_printf("> ");
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, file_name, ft_strlen(line) - 1))
		{
			close(fd);
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		close(fd);
	}
	fd = open(new_name, O_RDONLY);
	free(new_name);
	if (file->next == NULL)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	in_file(t_file *file, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (file->next == NULL)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (close(fd) == -1)
	{
		perror("close");
		exit(1);
	}
}

void	redirect_input(t_file *file, t_data *data, int pipefd[2])
{
	t_file	*tmp_file;

	(void)data;
	(void)pipefd;
	tmp_file = file;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == HEREDOC)
			heredoc(tmp_file, tmp_file->file_name);
		else if (tmp_file->type == QUOTE_HEREDOC)
			quote_heredoc(tmp_file, tmp_file->file_name);
		else if (tmp_file->type == IN_FILE)
			in_file(tmp_file, tmp_file->file_name);
		tmp_file = tmp_file->next;
	}
}
