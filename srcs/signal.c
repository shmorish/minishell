/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:12:41 by ryhara            #+#    #+#             */
/*   Updated: 2023/09/14 11:26:14 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	g_signal = 0;
}

void	signal_child_init(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	sigemptyset(&act1.sa_mask);
	act1.sa_handler = SIG_DFL;
	act1.sa_flags = 0;
	sigaction(SIGINT, &act1, NULL);
	sigemptyset(&act2.sa_mask);
	act2.sa_handler = SIG_DFL;
	act2.sa_flags = 0;
	sigaction(SIGQUIT, &act2, NULL);
}

void	signal_parent_init(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	sigemptyset(&act1.sa_mask);
	act1.sa_handler = SIG_IGN;
	act1.sa_flags = 0;
	sigaction(SIGINT, &act1, NULL);
	sigemptyset(&act2.sa_mask);
	act2.sa_handler = SIG_IGN;
	act2.sa_flags = 0;
	sigaction(SIGQUIT, &act2, NULL);
}

void	signal_heredoc(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	sigemptyset(&act1.sa_mask);
	act1.sa_sigaction = signal_handler_heredoc;
	act1.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act1, NULL);
	sigemptyset(&act2.sa_mask);
	act2.sa_sigaction = signal_handler_heredoc_quit;
	act2.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &act2, NULL);
}
