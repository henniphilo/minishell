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

void	here_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 148;
		ioctl(0, TIOCSTI, "\n");
	}
}

/* void	cat_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 130;
		write(1, "\n", 1);
	}
} */


