/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:54:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/29 15:13:28 by ryhara           ###   ########.fr       */
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
	char	*env_var;
	t_env	*next;
	t_env	*prev;
}	t_env;

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
	SEMICOLON
}			t_token_type;

typedef struct s_token
{
	t_token			*next;
	t_token			*prev;
	t_token_type	type;
	char			*data;
} t_token;

// buildin --------------------------------------------------------
// env_init.c
t_env	*head_init(void);
t_env	*env_init(char **envp);
// env_node_new.c
t_env	*node_new(char *str);
t_env	*node_new_with_plus(char *str);
// env_node_operate.c
void	node_add_front(t_env *head, t_env *new);
void	node_add_back(t_env *head, t_env *new);
void	node_delete(t_env *target);
t_env	*get_node_pos(t_env *head, char *str);
char	*get_env_var(t_env *env_head, char *env_name);
// ft_cd.c
void	ft_cd(char **list, t_env *env_head);
// ft_echo.c
void	ft_echo(char **list);
// ft_env.c
void	ft_env(char **list, t_env *env_head);
// ft_exit.c
void	ft_exit(char **list, t_env *env_head, t_data *data);
// ft_export_utils.c
bool	check_equal(char *str);
bool	check_duplicate_path(char *str, t_env *env_head);
void	change_path(char *str, t_env *target);
bool	check_plus(char *str);
void	join_path(char *str, t_env *target);
// ft_export.c
void	ft_export(char **list, t_env *env_head);
// ft_free.c
void	free_list(char **list);
void	head_free_all(t_env *head);
void	free_all(char **list, t_env *head);
void	node_free(t_env *node);
// ft_is_number_str.c
int		ft_is_number_str(char *s);
// ft_pwd.c
void	ft_pwd(void);
char	*get_pwd(void);
void	set_pwd(t_env *env_head, char *env_name);
// ft_split_once.c
char	**ft_split_once(char const *s, char c);
// ft_strccpy.c
char	*ft_strccpy(char *str, char c);
// ft_unset.c
void	ft_unset(char **list, t_env *env_head);
// is_long_overflow.c
bool	is_long_overflow(const char *str);
// other_commands.c
void	ft_other_command(char **list, t_env *env_head, t_data *data);
// path_utils.c
char	**path_split(char *path);
char	*check_path_access(char **path_list, char *command);
char	*get_env_var(t_env *env_head, char *env_name);
// select_commands.c
void	select_commands(char **list, t_env *env_head, t_data *data);

// lexer --------------------------------------------------------
// expansion_utils.c
bool	is_expansion(t_token_type type);
void	expansion_free(char *before_str, char *after_str, char *env_str);
void	expansion_join(t_token *node, char *before, char *after, char *env_str);
bool	count_doller(char *data, size_t *index);
// expansion.c
bool	is_expansion(t_token_type type);
bool	is_str_token(t_token_type type);
void	expansion(char *str, t_token *node, size_t start, size_t end, t_env *env_head);
void	expansion_env(char *data, t_token *node, size_t *index, t_env *env_head);
void	expansion_quote(t_token *node);
void expansion_check(t_token *token_head, t_env *env_head);
// lexer_boolean.c
bool	is_token(char c);
bool	is_only_space_before(char *line, size_t index);
bool	is_only_space_or_end(char *line, size_t index);
bool	is_valid_greater(char *line, size_t index);
bool	is_valid_lesser(char *line, size_t index);
// lexer_node_init.c
t_token	*token_head_init(void);
t_token	*token_init(char **envp);
void	token_head_free_all(t_token *head);
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
t_token *lexer(char *line, t_env *env_head);

// srcs ---------------------------------------------------------------------
// ft_get_list_size.c
size_t	ft_get_list_size(char **list);
// ft_puterr_utils.c
void	ft_puterr(char *s);
void	ft_put_command_err(char *s);
void	ft_puterr_env(char *s);
void	ft_put_not_valid(char *command, char *s);
// handle_quote.c
char	*handle_quote(char *line, t_env *env_head, t_data *data);
// signal.c
void	signal_init(void);

#endif