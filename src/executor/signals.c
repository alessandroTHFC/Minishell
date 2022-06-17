/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:21:15 by aboehm            #+#    #+#             */
/*   Updated: 2022/05/25 13:21:17 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	quit_process(int signal)
{
	(void)signal;
	safe_exit(0);
}

void	interrupt_process(int signal)
{
	(void)signal;
	write(2, "\n>>>", 4);
}

void	define_exec_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, quit_process);
}

void	define_input_signals(void)
{
	signal(SIGINT, interrupt_process);
	signal(SIGQUIT, SIG_IGN);
}
