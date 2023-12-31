/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:26:17 by shmorish          #+#    #+#             */
/*   Updated: 2023/09/22 12:55:14 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# define HEREDOC_FILE "/tmp/.heredoc"
# include <fcntl.h>

typedef struct s_parser			t_parser;
typedef struct s_file			t_file;
typedef enum e_redirect_type	t_redirect_type;

int		**make_pipefd(t_parser *parser_head);
void	close_pipefd(int pipefd[2]);
void	close_last_pipefd(int **pipefd);
void	free_pipefd(int **pipefd);
void	put_pipe(int **pipefd, int i);
int		fork_error(void);
int		dup_error_exit(int oldfd);
int		dup2_error_exit(int oldfd, int newfd);
bool	is_input_redirect(t_redirect_type type);
bool	is_output_redirect(t_redirect_type type);
int		pipe_error(int *pipefd);
int		close_error_exit(int fd);
pid_t	*count_process(t_parser *parser_head);
void	free_cmd(char **cmd);
void	redirect(t_parser *parser, t_data *data, int *status);
int		in_file(t_file *file, char *file_name, t_data *data, int *status);
int		append(t_file *file, char *file_name, t_data *data, int *status);
int		out_file(t_file *file, char *file_name, t_data *data, int *status);
// heredoc_expansion.c
char	*heredoc_join(char *before_l, char *after_l, char *envstr, size_t *i);
char	*heredoc_newline(char *newline, size_t *i, t_data *data);
char	*heredoc_expansion(char *line, t_data *data);
void	read_heredoc(char *new_name, char *file_name, t_data *data);
void	free_and_close(char *line, int fd);
// heredoc_utils.c
void	rm_heredoc_file(void);
char	*create_heredoc_file(void);
void	write_heredoc(int fd, char *line, t_data *data);
void	read_heredoc_quote(char *new_name, char *file_name);
bool	dup2_heredoc(t_file *file, int fd);
// heredoc.c
int		heredoc(t_file *file, char *file_name, t_data *data);
int		quote_heredoc(t_file *file, char *file_name, t_data *data);
#endif
