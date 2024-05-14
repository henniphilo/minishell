#include "../../incl/minishell.h"

__sighandler_t	ctrl_c_handler(int signum)
{
	free_data(shell);
}

void	handle_signals()
{
	if (isatty(0))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(, ctrl_d_handler);
		signal(SIGINT, ctrl_c_handler); //free_data, print exit, exit
	}
}
