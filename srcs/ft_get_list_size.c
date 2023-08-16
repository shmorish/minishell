/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_list_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:24:40 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 16:24:40 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_list_size(char **list)
{
	size_t	count;

	count = 0;
	if (list == NULL)
		return (count);
	while (list[count])
		count++;
	return (count);
}
