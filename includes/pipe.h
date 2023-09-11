/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:26:17 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/11 10:50:49 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# define HEREDOC_FILE ".heredoc"
# include <fcntl.h>

typedef struct s_parser	t_parser;
typedef struct s_file	t_file;

int		**make_pipefd(t_parser *parser_head);
void	close_pipefd(int pipefd[2]);
void	redirect_output(t_file *file_head, t_data *data, int pipefd[2]);
void	redirect_input(t_file *file_head, t_data *data, int pipefd[2]);
void	free_pipefd(int **pipefd);

// heredoc_utils.c
void	rm_heredoc_file(void);
char	*create_heredoc_file(void);
void	read_heredoc(char *new_name, char *file_name);
void	read_heredoc_expansion(char *new_name, char *file_name);
bool	dup2_heredoc(t_file *file, int fd);
// heredoc.c
void	heredoc(t_file *file, char *file_name);
void	quote_heredoc(t_file *file, char *file_name);
#endif
