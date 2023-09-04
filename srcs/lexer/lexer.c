/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:04:25 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/04 14:34:35 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_token_type(t_token *new)
{
	if (new->str == NULL)
		return ;
	else if (!ft_strncmp(new->str, ">>", 2))
		new->type = D_GREATER;
	else if (!ft_strncmp(new->str, ">", 1))
		new->type = S_GREATER;
	else if (!ft_strncmp(new->str, "<<", 2))
		new->type = D_LESSER;
	else if (!ft_strncmp(new->str, "<", 1))
		new->type = S_LESSER;
	else if (!ft_strncmp(new->str, "|", 1))
		new->type = PIPE;
	else if ((new->str)[0] == '\"')
		new->type = D_QUOTE;
	else if ((new->str)[0] == '\'')
		new->type = S_QUOTE;
	else
		new->type = STRING;
}

void	lexer_normal(char *line, size_t *index, t_token *token_head)
{
	size_t	start;
	char	*tmp;

	start = *index;
	while (line[*index] && !is_token(line[*index]) && line[*index] != ' ')
		(*index)++;
	tmp = ft_substr(line, start, *index - start);
	if (tmp == NULL)
		return ;
	token_node_add_back(token_head, token_node_new(tmp));
	if (line[*index] == ' ' && is_str_token(token_head->prev->type))
		token_head->prev->type = R_SPACE_STR;
	if (start > 0 && line[start - 1] == ' ' && is_str_token(token_head->prev->type))
		token_head->prev->type = L_SPACE_STR;
	free(tmp);
}

bool	lexer_select(char *line, size_t *index)
{
	if (line[*index] == '\'')
		return (lexer_single_quote(line, index));
	else if (line[*index] == '\"')
		return (lexer_double_quote(line, index));
	else if (line[*index] == '|')
		return (lexer_pipe(line, index));
	else if (line[*index] == '>')
		return (lexer_greater(line, index));
	else if (line[*index] == '<')
		return (lexer_lesser(line, index));
	return (true);
}

bool	lexer_token(char *line, size_t *index, t_token *token_head)
{
	size_t	start;
	char	*tmp;

	start = *index;
	if (!lexer_select(line, index))
		return (false);
	tmp = ft_substr(line, start, *index - start + 1);
	if (tmp == NULL)
		return (false);
	token_node_add_back(token_head, token_node_new(tmp));
	if (line[start - 1] == ' ' && token_head->prev->type == D_QUOTE)
		token_head->prev->type = LSP_D_QUOTE;
	else if (line[start - 1] == ' ' && token_head->prev->type == S_QUOTE)
		token_head->prev->type = LSP_S_QUOTE;
	free(tmp);
	return (true);
}

t_token	*lexer(char *line, t_env *env_head, t_data *data)
{
	size_t	index;
	t_token	*token_head;

	index = 0;
	token_head = token_head_init();
	if (line[index] == '\0')
		return (NULL);
	while (line[index])
	{
		if (is_token(line[index]))
		{
			if (lexer_token(line, &index, token_head))
				index++;
			else
			{
				data->exit_status = 258;
				free_token_head_all(token_head);
				return (NULL);
			}
		}
		else if (line[index] == ' ')
		{
			while (line[index] == ' ')
				index++;
		}
		else
			lexer_normal(line, &index, token_head);
	}
	ft_printf("\n----------- lexer start-------------\n");
	print_lexer(token_head);
	ft_printf("---------- expansion start ---------\n");
	expansion_check(token_head, env_head);
	if (is_str_token(token_head->next->type))
		token_head->next->type = COMMAND;
	data->exit_status = 0;
	print_lexer(token_head);
	// free_token_head_all(token_head);
	ft_printf("----------- lexer end --------------\n\n");
	return (token_head);
	// return (NULL);
}
