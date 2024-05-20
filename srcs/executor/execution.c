#include "../../incl/minishell.h"

// darf zb bei unset USER | env nur env ausfuehren USER bleibt bestehen...
int		pipeline_exe(t_data *shell)
{
	t_command	*toex;
	int			i;

	i = 0;
	toex = shell->toex;
	init_pipeline(shell);
	while(toex)
	{
		if (builtin_check(toex->cmd) == 1)
		{
			if (which_builtin_parent(shell, toex->cmd) != 0)
			{
				free_pipes(shell);
				free (shell->pids);
				shell->pids = NULL;
				free (shell->fd);
				return (1);
			}
		}
		else
		{
			if (exe_env(shell, shell->pids, i, toex) != 0)
			{
				perror("exe Error\n");
				g_estatus = 1;
				return (1);
			}
		}
		toex = toex->next;
		i++;
	}
	wait_for_children(shell);
	free_pipes(shell);
	free (shell->pids);
	shell->pids = NULL;
	free (shell->fd); //problematic double free if its null noch protecten
	return(0);
}
