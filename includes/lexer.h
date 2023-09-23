/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:00:12 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/23 14:52:23 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdbool.h>

# define ERR_NEWLINE "minishell: syntax error near unexpected token `newline'\n"
# define ERR_PIPE "minishell: syntax error near unexpected token `|'\n"
# define ERR_QUOTE "minishell: syntax error: quote is not closed.\n"

typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_data		t_data;
typedef enum e_token_type	t_token_type;

// lexer --------------------------------------------------------
// expansion_check.c
t_token	*expansion_last(t_token *tmp_node);

void	expansion_check(t_token *token_head, t_data *data);
// expansion_utils.c
void	expansion_free(char *before_str, char *after_str, char *env_str);
void	expansion_check_space(t_token *node);
void	expansion_join(t_token *node, char *before, char *after, char *env_str);
bool	count_doller(char *data, size_t *index);
bool	expansion_check_doll_end(char *str, size_t *index);
// expansion.c
void	expansion(char *env_val, t_token *node, size_t start, size_t end);
char	*expansion_get_env_val(char *env_name, t_env *env_head, t_data *data);
bool	expansion_env(char *str, t_token *node, size_t *index, t_data *data);
void	expansion_quote(t_token *node);
t_token	*expansion_split(t_token *node);
// ft_split_charset.c
char	**ft_split_charset(char *str, char *charset);
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
// lexer_boolean3.c
bool	lexer_token_main(char *line, size_t *index,
			t_token *head, t_data *data);
bool	is_left_space(t_token_type type);
bool	is_no_space(t_token_type type);
bool	is_heredoc_expansion(t_token *node);
bool	is_env_name(char c);
// lexer_node_init.c
t_token	*token_head_init(void);
t_token	*token_init(char **envp);
void	free_token_head_all(t_token *head);
void	set_token_type(t_token *new_node);
bool	lexer_select(char *line, size_t *index);
// lexer_node.c
t_token	*token_node_new(char *str);
void	token_node_add_back(t_token *head, t_token *new_node);
void	token_node_add_front(t_token *head, t_token *new_node);
void	token_node_insert(t_token *node, t_token *new_node);
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
void	lexer_normal(char *line, size_t *index, t_token *token_head);
bool	lexer_token(char *line, size_t *index, t_token *token_head);
bool	lexer_token_main(char *line, size_t *index,
			t_token *token_head, t_data *data);
t_token	*lexer(char *line, t_data *data);

#endif