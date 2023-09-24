/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 09:03:41 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/22 12:17:06 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	heredoc(t_file *file, char *file_name, t_data *data)
{
	int		fd;
	char	*new_name;

	(void)data;
	(void)file;
	new_name = create_heredoc_file();
	if (new_name == NULL)
		return (0);
	fd = open(new_name, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		free(new_name);
		data->exit_status = 1;
		exit(1);
	}
	close(fd);
	read_heredoc(new_name, file_name, data);
	fd = open(new_name, O_RDONLY);
	free(new_name);
	data->exit_status = 0;
	return (fd);
}

int	quote_heredoc(t_file *file, char *file_name, t_data *data)
{
	int		fd;
	char	*new_name;

	(void)data;
	(void)file;
	new_name = create_heredoc_file();
	if (new_name == NULL)
		return (0);
	fd = open(new_name, O_CREAT, 0644);
	if (fd == -1)
	{
		perror("open");
		free(new_name);
		data->exit_status = 1;
		exit(1);
	}
	close(fd);
	read_heredoc_quote(new_name, file_name);
	fd = open(new_name, O_RDONLY);
	free(new_name);
	data->exit_status = 0;
	return (fd);
}
