/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:04:25 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 13:09:06 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lexer_normal(char *line, size_t *index, t_token *token_head)
{
	size_t	start;
	char	*tmp;

	start = *index;
	while (line[*index] && !is_token(line[*index]) && !ft_isspace(line[*index]))
		(*index)++;
	tmp = ft_substr(line, start, *index - start);
	if (tmp == NULL)
		return ;
	token_node_add_back(token_head, token_node_new(tmp));
	if (ft_isspace(line[*index]) && is_str_token(token_head->prev->type))
		token_head->prev->type = R_SPACE_STR;
	if (start > 0 && ft_isspace(line[start - 1])
		&& is_str_token(token_head->prev->type))
		token_head->prev->type = L_SPACE_STR;
	free(tmp);
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
	if (start > 0 && ft_isspace(line[start - 1])
		&& token_head->prev->type == D_QUOTE)
		token_head->prev->type = LSP_D_QUOTE;
	else if (start > 0 && ft_isspace(line[start - 1])
		&& token_head->prev->type == S_QUOTE)
		token_head->prev->type = LSP_S_QUOTE;
	free(tmp);
	return (true);
}

bool	lexer_token_main(char *line, size_t *index, t_token *head, t_data *data)
{
	if (lexer_token(line, index, head))
	{
		(*index)++;
		return (true);
	}
	else
	{
		data->exit_status = 258;
		free_token_head_all(head);
		return (false);
	}
}

void	expansion_check(t_token *token_head, t_data *data)
{
	t_token	*tmp_node;
	size_t	index;

	tmp_node = token_head->next;
	while (tmp_node != token_head)
	{
		index = 0;
		while (tmp_node->str[index])
		{
			if (tmp_node->str[index] == '$' && is_expansion(tmp_node->type))
			{
				if (tmp_node->prev->type != D_LESSER)
					expansion_env(tmp_node->str, tmp_node, &index, data);
			}
			index++;
		}
		expansion_quote(tmp_node);
		if (tmp_node->type == DELETE)
			tmp_node = expansion_split(tmp_node);
		if (tmp_node == NULL)
			return ;
		tmp_node = tmp_node->next;
	}
}

t_token	*lexer(char *line, t_data *data)
{
	size_t	index;
	t_token	*token_head;

	index = 0;
	token_head = token_head_init();
	while (line[index])
	{
		if (is_token(line[index]))
		{
			if (!lexer_token_main(line, &index, token_head, data))
				return (NULL);
		}
		else if (ft_isspace(line[index]))
		{
			while (ft_isspace(line[index]))
				index++;
		}
		else
			lexer_normal(line, &index, token_head);
	}
	expansion_check(token_head, data);
	return (token_head);
}

// ft_printf("\n----------- lexer start-------------\n");
// print_lexer(token_head);
// ft_printf("---------- expansion start ---------\n");
// expansion_check(token_head, data);
// print_lexer(token_head);
// ft_printf("----------- lexer end --------------\n\n");