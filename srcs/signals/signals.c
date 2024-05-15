#include "../../incl/minishell.h"

static void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 130;
		ft_putstr_fd("\n", 0);
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
//treat heredocs differently
/* pbencze@c4a10c10:~/Documents/42cursus/Minishell/Minishell_Github$ cat << h | echo hi
> hello
>
bash: warning: here-document at line 5 delimited by end-of-file (wanted `h')
hi */


