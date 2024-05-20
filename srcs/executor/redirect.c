#include "../../incl/minishell.h"


void	redirect_pipes(t_data *shell)
{
	if(shell->toex->fd_in != -2) // <
	{
		if (dup2(shell->toex->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in fail");
			close(shell->toex->fd_in);
			g_estatus = 1;
			return ;
		}
		close(shell->toex->fd_in);
	}
	if (shell->toex->fd_out != -2) // > >>
	{
		if (dup2(shell->toex->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out fail");
			close(shell->toex->fd_out);
			g_estatus = 1;
			return ;
		}
		close(shell->toex->fd_out);
	}
}
