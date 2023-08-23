/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:54:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/21 12:29:49 by morishitash      ###   ########.fr       */
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

typedef struct s_env
{
	char			*env_name;
	char			*env_var;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

typedef struct s_args
{
	char			**args;
	char			*sign;
	// size_t			index;
	struct s_args	*right;
	struct s_args	*left;
}					t_args;

int					ft_is_number_str(char *s);
size_t				ft_get_list_size(char **list);
void				ft_puterr(char *s);
void				ft_put_command_err(char *s);
void				ft_put_too_arg_err(char *s);
void				ft_put_few_arg_err(char *s);
void				free_list(char **list);
void				head_free_all(t_env *head);
void				free_all(char **list, t_env *head);
void				node_free(t_env *node);

void				select_commands(char **list, t_env *env_head);
void				ft_exit(char **list, t_env *env_head);
void				ft_echo(char **list);
void				ft_pwd(void);
void				ft_cd(char **list);
void				ft_env(char **list, t_env *env_head);
void				ft_export(char **list, t_env *env_head);
void				ft_unset(char **list, t_env *env_head);
void				ft_other_command(char **list, t_env *env_head);

t_env				*node_new(char *str);
void				node_add_front(t_env *head, t_env *new);
void				node_add_back(t_env *head, t_env *new);
void				node_delete(t_env *target);
t_env				*get_node_pos(t_env *head, char *str);
t_env				*head_init(void);
t_env				*env_init(char **envp);
bool				check_equal(char *str);
bool				check_duplicate_path(char *str, t_env *env_head);

char	*handle_quote(char *line, t_env *env_head);

#endif