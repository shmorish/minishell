/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:19:54 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/08 14:52:52 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*free_parser_cmd(t_parser **tmp)
{
	int	i;

	i = 0;
	while ((*tmp)->cmd[i] != NULL)
	{
		free((*tmp)->cmd[i]);
		i++;
	}
	free((*tmp)->cmd);
	return (NULL);
}

static void	*free_dup_null(char **tmp_cmd, t_parser **tmp)
{
	int	i;

	i = 0;
	while (tmp_cmd[i] != NULL)
	{
		free(tmp_cmd[i]);
		i++;
	}
	free(tmp_cmd);
	free_parser_cmd(tmp);
	return (NULL);
}

static void	*parser_cmd_init(t_parser **tmp, t_token **tmp_token)
{
	(*tmp)->cmd = (char **)malloc(sizeof(char *) * 2);
	if ((*tmp)->cmd == NULL)
		return (NULL);
	(*tmp)->cmd[0] = ft_strdup((*tmp_token)->str);
	if ((*tmp)->cmd[0] == NULL)
		return (NULL);
	(*tmp)->cmd[1] = NULL;
	return (tmp);
}

static void	*put_cmd_to_parser(t_parser **tmp, char **tmp_cmd,
			t_token **tmp_token)
{
	int	i;

	i = 0;
	while ((*tmp)->cmd[i] != NULL)
	{
		tmp_cmd[i] = ft_strdup((*tmp)->cmd[i]);
		if (tmp_cmd[i++] == NULL)
			return (free_dup_null(tmp_cmd, tmp));
	}
	tmp_cmd[i] = ft_strdup((*tmp_token)->str);
	tmp_cmd[i + 1] = NULL;
	free_parser_cmd(tmp);
	(*tmp)->cmd = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tmp_cmd[i] != NULL)
	{
		(*tmp)->cmd[i] = ft_strdup(tmp_cmd[i]);
		if ((*tmp)->cmd[i++] == NULL)
			return (free_parser_cmd(tmp));
	}
	(*tmp)->cmd[i] = NULL;
	i = 0;
	while (tmp_cmd[i] != NULL)
		free(tmp_cmd[i++]);
	free(tmp_cmd);
	return (tmp);
}

void	*parser_cmd(t_token **tmp_token, t_parser **tmp)
{
	char	**tmp_cmd;
	int		i;

	i = 0;
	if ((*tmp)->cmd == NULL)
	{
		if (parser_cmd_init(tmp, tmp_token) == NULL)
			return (NULL);
	}
	else
	{
		while ((*tmp)->cmd[i] != NULL)
			i++;
		tmp_cmd = (char **)malloc(sizeof(char *) * (i + 2));
		if (tmp_cmd == NULL)
			return (free_parser_cmd(tmp));
		if (put_cmd_to_parser(tmp, tmp_cmd, tmp_token) == NULL)
			return (NULL);
	}
	return (tmp);
}
