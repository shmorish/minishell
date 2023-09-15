/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errno.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morishitashoto <morishitashoto@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:46:01 by morishitash       #+#    #+#             */
/*   Updated: 2023/09/15 16:57:04 by morishitash      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_errno(char *s)
{
	ft_puterr("minishell: ");
	ft_puterr(s);
	ft_puterr(": ");
	ft_puterr(strerror(errno));
	ft_puterr("\n");
}
