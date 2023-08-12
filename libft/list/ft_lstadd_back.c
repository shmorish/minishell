/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:18:30 by shmorish          #+#    #+#             */
/*   Updated: 2023/07/31 17:37:40 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_list.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*output;

	if (new == NULL)
		return ;
	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			output = ft_lstlast(*lst);
			output->next = new;
		}
	}
}
