/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:54:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/06 19:00:54 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
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

extern int g_signal;
typedef struct s_token	t_token;
typedef struct s_env	t_env;

typedef struct s_data
{
	t_env	*env_head;
	t_token	*token_head;
	char	**list;
	char	**envp;
	int		exit_status;
	int		process_id;
}					t_data;

typedef struct s_env
{
	char	*env_name;
	char	*env_val;
	t_env	*next;
	t_env	*prev;
}	t_env;

// 	EMPTY, // 0
//	PIPE, // 1
//	S_QUOTE, // 2
//	LSP_S_QUOTE, // 3
//	D_QUOTE, // 4
//	LSP_D_QUOTE, // 5
// S_GREATER, // 6
// D_GREATER, // 7
// S_LESSER, // 8
// D_LESSER, // 9
// COMMAND, // 10
// FILE_OR_DIR, // 11
// STRING, // 12
// R_SPACE_STR, // 13
// L_SPACE_STR, // 14
// SEMICOLON, // 15
// INCLUDE_QUOTE // 16
typedef enum e_token_type {
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
	INCLUDE_QUOTE
}			t_token_type;

typedef struct s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*str;
}	t_token;

typedef enum e_while_type {
	BREAK,
	CONTINUE,
	THROUGH
}			t_while_type;

typedef struct s_parser	t_parser;
typedef struct s_file	t_file;

// 	QUOTE_HEREDOC << "" or << ''
//  HEREDOC <<
//  IN_FILE <
//  OUT_FILE >
//  APPEND >>
typedef enum e_redirect_type {
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}	t_redirect_type;

// typedef struct s_input
// {
// 	char			*file_name;
// 	t_redirect_type	type;
// 	t_input			*next;
// }	t_input;

// typedef struct s_output
// {
// 	char			*file_name;
// 	t_redirect_type	type;
// 	t_output		*next;
// }	t_output;

typedef struct s_file
{
	char			*file_name;
	t_redirect_type	type;
	t_file			*next;
}	t_file;

typedef struct s_parser
{
	char			**cmd;
	t_file			*input;
	t_file			*output;
	t_parser		*next;
	t_parser		*prev;
}	t_parser;

// buildin --------------------------------------------------------
// env_init.c
t_env	*head_init(void);
t_env	*env_init(char **envp);
// env_list_to_array.c
char	**env_list_to_char_arr(t_env *env_head);
// env_node_new.c
t_env	*node_new(char *str);
t_env	*node_new_with_plus(char *str);
// env_node_operate.c
void	node_add_front(t_env *head, t_env *new);
void	node_add_back(t_env *head, t_env *new);
void	node_delete(t_env *target);
t_env	*get_node_pos(t_env *head, char *str);
char	*get_env_val(t_env *env_head, char *env_name);
// ft_cd.c
void	ft_cd(char **array, t_env *env_head, t_data *data);
// ft_echo.c
void	ft_echo(char **array, t_data *data);
// ft_env.c
void	ft_env(char **array, t_env *env_head, t_data *data);
// ft_exit.c
void	ft_exit(char **array, t_env *env_head, t_data *data);
// ft_export_utils.c
bool	check_equal(char *str);
bool	check_duplicate_path(char *str, t_env *env_head);
void	change_path(char *str, t_env *target);
bool	check_plus(char *str);
void	join_path(char *str, t_env *target);
// ft_export.c
void	ft_export(char **list, t_env *env_head, t_data *data);
// ft_free.c
void	free_char_array(char **array);
void	free_env_node(t_env *node);
void	free_env_head_all(t_env *head);
void	free_all(char **array, t_env *head);
// ft_is_number_str.c
int		ft_is_number_str(char *s);
// ft_pwd.c
void	ft_pwd(t_data *data);
char	*get_pwd(void);
void	set_pwd(t_env *env_head, char *env_name);
// ft_split_once.c
char	**ft_split_once(char const *s, char c);
// ft_strccpy.c
char	*ft_strccpy(char *str, char c);
// ft_unset.c
void	ft_unset(char **array, t_env *env_head, t_data *data);
// is_long_overflow.c
bool	is_long_overflow(const char *str);
// other_commands.c
void	ft_other_command(char **array, t_env *env_head, t_data *data);
// other_commands_utils.c
char	**path_split(char *path);
char	*check_path_access(char **path_list, char *command, t_data *data);
// select_commands.c
void	select_commands(char **list, t_env *env_head, t_data *data);

// lexer --------------------------------------------------------
// expansion_utils.c
void	expansion_free(char *before_str, char *after_str, char *env_str);
void	expansion_join(t_token *node, char *before, char *after, char *env_str);
bool	count_doller(char *data, size_t *index);
bool	expansion_check_doll_end(char *str, size_t *index);
// expansion.c
void	expansion(char *env_val, t_token *node, size_t start, size_t end);
char	*expansion_get_env_val(char *env_name, t_env *env_head);
void	expansion_env(char *data, t_token *node, size_t *index, t_env *head);
void	expansion_quote(t_token *node);
void	expansion_check(t_token *token_head, t_env *env_head);
// lexer_boolean.c
bool	is_token(char c);
bool	is_expansion(t_token_type type);
bool	is_str_token(t_token_type type);
bool	is_quote(t_token_type type);
// lexer_boolean2.c
bool	is_only_space_before(char *line, size_t index);
bool	is_only_space_or_end(char *line, size_t index);
bool	is_valid_greater(char *line, size_t index);
bool	is_valid_lesser(char *line, size_t index);
// lexer_node_init.c
t_token	*token_head_init(void);
t_token	*token_init(char **envp);
void	free_token_head_all(t_token *head);
// lexer_node.c
t_token	*token_node_new(char *str);
void	token_node_add_back(t_token *head, t_token *new);
void	token_node_add_front(t_token *head, t_token *new);
void	token_node_delete(t_token *target);
// lexer_partial.c
bool	lexer_single_quote(char *line, size_t *index);
bool	lexer_double_quote(char *line, size_t *index);
bool	lexer_pipe(char *line, size_t *index);
bool	lexer_greater(char *line, size_t *index);
bool	lexer_lesser(char *line, size_t *index);
// lexer_print.c
void	print_enum(t_token *node);
void	print_lexer(t_token *token_head);
// lexer.c
void	set_token_type(t_token *new);
void	lexer_normal(char *line, size_t *index, t_token *token_head);
bool	lexer_token(char *line, size_t *index, t_token *token_head);
t_token	*lexer(char *line, t_env *env_head, t_data *data);

// srcs ---------------------------------------------------------------------
// ft_get_list_size.c
size_t	ft_get_list_size(char **list);
// ft_puterr_utils.c
void	ft_puterr(char *s);
void	ft_puterr_set_status(char *s, t_data *data, int number);
void	ft_puterr_command(char *s, t_data *data);
void	ft_puterr_permit(char *s);
void	ft_puterr_valid_identifer(char *command, char *s, t_data *data);
// ft_puterr_utils2.c
void	ft_puterr_env(char *s);
void	ft_perror_set_status(char *str, int number, t_data *data);
// handle_quote.c
char	*handle_quote(char *line, t_env *env_head, t_data *data);
// signal.c
void	signal_handler_sigint(int signum, siginfo_t *info, void *ucontext);
void	signal_handler_sigquit(int signum, siginfo_t *info, void *ucontext);
void	signal_handler_child(int signum, siginfo_t *info, void *ucontext);
void	signal_main_init(void);
void	signal_exe_init(void);

// parser --------------------------------------------------------
// free_parser.c
void	free_parser_head_all(t_parser *head);
void	*free_parser_null(t_parser *parser_head);
// parser.c
t_parser	*parser(t_token *token_head);
// parser_bool.c
bool	can_connect_start(t_token *token_head);
bool	can_connect(t_token *token_head);
bool	is_connectable_quote(t_token *token_head);
bool	is_redirect(t_token *token_head);
// token_evoluver.c
void	evoluve_token(t_token *token_head);
// parser_node.c
t_parser	*parser_node_new(void);
t_parser	*parser_init(void);
// print_parser.c
void	print_parser(t_parser *parser_head);
// parser_pipe.c
void	*parser_pipe(t_parser **tmp, t_parser *parser_head);
// parser_redirect.c
void	*parser_redirect(t_token **tmp_token, t_parser **tmp);
// parser_cmd.c
void	*parser_cmd(t_token **tmp_token, t_parser **tmp);

#endif