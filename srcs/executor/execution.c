#include "../../incl/minishell.h"

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
			which_builtin_parent(shell, toex->cmd);
		else
		{
			if (exe_env(shell, shell->pids, i, toex) == 1)
			{
				perror("exe Error\n");
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
