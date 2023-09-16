/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:08:51 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 12:54:24 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser	t_parser;
typedef struct s_token	t_token;

// parser --------------------------------------------------------
// free_parser.c
void		free_parser_head_all(t_parser *head);
void		*free_parser_null(t_parser *parser_head);
// parser.c
t_parser	*parser(t_token *token_head);
// parser_bool.c
bool		can_connect_start(t_token *token_head);
bool		can_connect(t_token *token_head);
bool		is_connectable_quote(t_token *token_head);
bool		is_redirect(t_token *token_head);
bool		is_string(t_token_type type);
// token_evoluver.c
void		evoluve_token(t_token *token_head);
// parser_node.c
t_parser	*parser_node_new(void);
t_parser	*parser_init(void);
// print_parser.c
void		print_parser(t_parser *parser_head);
// parser_pipe.c
void		*parser_pipe(t_parser **tmp, t_parser *parser_head);
// parser_redirect.c
void		*parser_redirect(t_token **tmp_token, t_parser **tmp);
// parser_cmd.c
void		*parser_cmd(t_token **tmp_token, t_parser **tmp);
// parser_cmd_free.c
void		*free_parser_cmd(t_parser **tmp);
void		*free_dup_null(char **tmp_cmd);
void		*free_dup_cmd_null(char **tmp_cmd, t_parser **tmp);

#endif