/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:19:55 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/23 17:50:44 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 130;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	if (isatty(0))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_handler);
	}
}

static void	sig_handler_children(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 130;
		ft_putstr_fd("\n", 1);
	}
	if (signum == SIGQUIT)
	{
		g_estatus = 131;
		ft_putstr_fd("Core dumped\n", 1);
	}
}

void	handle_signals_children(void)
{
	signal(SIGQUIT, sig_handler_children);
	signal(SIGINT, sig_handler_children);
}

void	here_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 148;
		ioctl(0, TIOCSTI, "\n");
	}
}
