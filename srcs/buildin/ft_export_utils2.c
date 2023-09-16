/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 11:18:27 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/16 16:28:25 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_include_equal(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (false);
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}
