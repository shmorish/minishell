/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:04:25 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/23 14:15:04 by ryhara           ###   ########.fr       */
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
		return (ft_puterr_malloc());
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

t_token	*expansion_last(t_token *tmp_node)
{
	expansion_quote(tmp_node);
	if (tmp_node->type == DELETE)
		tmp_node = expansion_split(tmp_node);
	if (tmp_node == NULL)
		return (ft_puterr_malloc(), NULL);
	return (tmp_node);
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
				if (!is_env_name(tmp_node->str[index + 1]))
					index++;
				else if (!is_heredoc_expansion(tmp_node))
				{
					if (expansion_env(tmp_node->str, tmp_node, &index, data))
						index = 0;
				}
			}
			if (tmp_node->str[0] != '\0' || tmp_node->str[0] != '$')
				index++;
		}
		tmp_node = expansion_last(tmp_node);
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
