/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:09:25 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/12 13:09:46 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_sigint(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	(void)info;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_sigquit(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	(void)info;
	rl_on_new_line();
	rl_redisplay();
}