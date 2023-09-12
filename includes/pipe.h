/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:26:17 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/12 13:01:10 by ryhara           ###   ########.fr       */
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
void	close_last_pipefd(int **pipefd);
void	redirect_output(t_file *file_head, t_data *data, int pipefd[2]);
void	redirect_input(t_file *file_head, t_data *data, int pipefd[2]);
void	free_pipefd(int **pipefd);
void	put_pipe(int **pipefd, int i);

// heredoc_utils.c
void	rm_heredoc_file(void);
char	*create_heredoc_file(void);
void	read_heredoc(char *new_name, char *file_name);
void	read_heredoc_expansion(char *new_name, char *file_name);
bool	dup2_heredoc(t_file *file, int fd);
// heredoc.c
void	heredoc(t_file *file, char *file_name, t_data *data);
void	quote_heredoc(t_file *file, char *file_name, t_data *data);
#endif
