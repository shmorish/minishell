/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:12:41 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/04 18:57:41 by ryhara           ###   ########.fr       */
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
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_child(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	(void)info;
	g_signal = signum;
	ft_printf("signal ignore\n");
}

void	signal_main_init(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	sigemptyset(&act1.sa_mask);
	act1.sa_sigaction = signal_handler_sigint;
	act1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act1, NULL);
	sigemptyset(&act2.sa_mask);
	act2.sa_sigaction = signal_handler_sigquit;
	act2.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act2, NULL);
}

void	signal_exe_init(void)
{
	struct sigaction	act1;

	sigemptyset(&act1.sa_mask);
	act1.sa_sigaction = signal_handler_child;
	act1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act1, NULL);
}
