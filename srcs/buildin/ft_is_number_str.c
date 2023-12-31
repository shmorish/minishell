/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_number_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:59:55 by ryhara            #+#    #+#             */
/*   Updated: 2023/08/10 17:59:55 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_number_str(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	if (s[i] == '\0')
		return (0);
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

// Error handling "-0" "+0" "-" "+" ???