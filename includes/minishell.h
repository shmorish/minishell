/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:54:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/14 12:24:41 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "./buildin.h"
# include "./lexer.h"
# include "./parser.h"
# include "./pipe.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
#include <sys/stat.h>

extern int				g_signal;
typedef struct s_token	t_token;
typedef struct s_env	t_env;

typedef struct s_data
{
	t_env				*env_head;
	t_token				*token_head;
	char				**list;
	char				**envp;
	int					exit_status;
	int					process_id;
}						t_data;

typedef struct s_env
{
	char				*env_name;
	char				*env_val;
	t_env				*next;
	t_env				*prev;
}						t_env;

typedef enum e_token_type
{
	EMPTY,
	PIPE,
	S_QUOTE,
	LSP_S_QUOTE,
	D_QUOTE,
	LSP_D_QUOTE,
	S_GREATER,
	D_GREATER,
	S_LESSER,
	D_LESSER,
	COMMAND,
	FILE_OR_DIR,
	STRING,
	R_SPACE_STR,
	L_SPACE_STR,
	SEMICOLON,
	INCLUDE_QUOTE,
	DELETE,
}						t_token_type;

typedef struct s_token
{
	t_token				*next;
	t_token				*prev;
	t_token_type		type;
	char				*str;
}						t_token;

typedef enum e_while_type
{
	BREAK,
	CONTINUE,
	THROUGH
}						t_while_type;

typedef struct s_parser	t_parser;
typedef struct s_file	t_file;

// 	QUOTE_HEREDOC << "" or << ''
//  HEREDOC <<
//  IN_FILE <
//  OUT_FILE >
//  APPEND >>
typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}						t_redirect_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	t_file				*next;
}						t_file;

typedef struct s_parser
{
	char				**cmd;
	t_file				*input;
	t_file				*output;
	t_parser			*next;
	t_parser			*prev;
}						t_parser;

typedef struct s_pid	t_pid;

typedef struct s_pid
{
	pid_t	*pid;
	pid_t	end_pid;
	pid_t	stdin_fd;
	pid_t	stdout_fd;
	int		**pipe_fd;
}	t_pid;

// srcs ---------------------------------------------------------------------
// ascii.c
void	print_ascii(void);
// ft_puterr_utils.c
void	ft_puterr(char *s);
void	ft_puterr_set_status(char *s, t_data *data, int number);
void	ft_puterr_command(char *s, t_data *data);
void	ft_puterr_permit(char *s);
void	ft_puterr_valid_identifer(char *command, char *s, t_data *data);
// ft_puterr_utils2.c
void	ft_puterr_env(char *s);
void	ft_strerror_cd(char *str, int number, t_data *data);
void	*ft_puterr_malloc(void);
void	ft_puterr_nofile(char *s);
void	ft_puterr_isdir(char *s);
// signal_handler.c
void	signal_handler_sigint(int signum, siginfo_t *info, void *ucontext);
void	signal_handler_sigquit(int signum, siginfo_t *info, void *ucontext);
void	signal_handler_heredoc(int signum, siginfo_t *info, void *ucontext);
void	signal_handler_heredoc_quit(int signum,
			siginfo_t *info, void *ucontext);
// signal.c
void	signal_main_init(void);
void	signal_child_init(void);
void	signal_parent_init(void);
void	signal_heredoc(void);

// no_pipe_main.c
void	no_pipe_main(t_parser *parser, t_data *data);
// have_pipe_main.c
void	*have_pipe_main(t_parser *parser_head, t_data *data);
// have_pipe_utils.c
void	next_pipe(t_pid *pid_data, int i);
void	prev_pipe(t_pid *pid_data, int i);
void	put_back_fd(t_pid *pid_data);
void	parent_close_pipe(t_pid *pid_data, int i);
int		wait_error_exit(int *status);
#endif