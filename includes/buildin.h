/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:00:15 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 18:01:59 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include <stdbool.h>
# include <sys/stat.h>

typedef struct s_env			t_env;
typedef struct s_data			t_data;
typedef enum e_proccess_type	t_proccess_type;

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
void	node_add_front(t_env *head, t_env *new_node);
void	node_add_back(t_env *head, t_env *new_node);
void	node_delete(t_env *target);
t_env	*get_node_pos(t_env *head, char *str);
char	*get_env_val(t_env *env_head, char *env_name);
// ft_cd.c
void	ft_cd(char **array, t_env *env_head, t_data *data);
// ft_echo.c
void	ft_echo(char **array, t_data *data);
// ft_env.c
void	ft_env(char **array, t_env *env_head, t_data *data);
// ft_exit_error.c
void	exit_numeric_error(char *str, t_data *data, t_proccess_type type);
void	exit_arg_error(t_data *data, t_proccess_type type);
// ft_exit.c
void	ft_exit(char **array, t_env *env_head,
			t_data *data, t_proccess_type type);
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
// other_command_check.c
bool	check_simple_access(char **path_list, char *command, t_data *data);
char	*check_path_access(char **path_list, char *command, t_data *data);
bool	check_directory(char *command, t_data *data);
void	check_permit(char **array, t_data *data, char **command);
// other_commands_utils.c
char	*path_join(char **path_list, char *command, int pos);
char	**path_split(char *path);
// other_commands.c
void	ft_other_command(char **array, t_env *env_head, t_data *data);
// select_commands.c
void	select_commands(char **array, t_env *env_head, t_data *data,
			t_proccess_type type);

#endif