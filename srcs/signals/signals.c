#include "../../incl/minishell.h"

static void	ctrl_c_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_estatus = 130;
		rl_replace_line("", 0);
		ft_putendl_fd(0, 0);
		rl_redisplay();
		rl_on_new_line();
	}
}

void	handle_signals(t_data *shell)
{
	if (isatty(0))
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ctrl_c_handler);
	}
	if (g_estatus)
		shell->estatus = g_estatus;
	g_estatus = 0;
}
//treat heredocs differently
/* pbencze@c4a10c10:~/Documents/42cursus/Minishell/Minishell_Github$ cat << h | echo hi
> hello
>
bash: warning: here-document at line 5 delimited by end-of-file (wanted `h')
hi */


