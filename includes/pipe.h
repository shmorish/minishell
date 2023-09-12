/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:26:17 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/12 22:57:02 by morishitash      ###   ########.fr       */
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
int		fork_error_exit(void);
int		dup_error_exit(int oldfd);
int		dup2_error_exit(int oldfd, int newfd);
void	pipe_error_exit(int *pipefd);
int		close_error_exit(int fd);
// heredoc_expansion.c
char	*heredoc_join(char *before_l, char *after_l, char *envstr, size_t *i);
char	*heredoc_newline(char *newline, size_t *i, t_data *data);
char	*heredoc_expansion(char *line, t_data *data);
void	read_heredoc(char *new_name, char *file_name, t_data *data);
// heredoc_utils.c
void	rm_heredoc_file(void);
char	*create_heredoc_file(void);
void	write_heredoc(int fd, char *line, t_data *data);
void	read_heredoc_quote(char *new_name, char *file_name);
bool	dup2_heredoc(t_file *file, int fd);
// heredoc.c
void	heredoc(t_file *file, char *file_name, t_data *data);
void	quote_heredoc(t_file *file, char *file_name, t_data *data);
#endif
