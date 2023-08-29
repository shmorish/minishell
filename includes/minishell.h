/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:54:48 by morishitash       #+#    #+#             */
/*   Updated: 2023/08/29 13:05:18 by morishitash      ###   ########.fr       */
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

typedef struct s_data
{
	t_env	*env_head;
	char	**list;
	char	**envp;
	int		exit_status;
	int		process_id;
}					t_data;

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
// ft_split_quote.c
char	**ft_split_quote(char const *s, char c);
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