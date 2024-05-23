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
		if(valid_fd_in_out_check(toex) == 1)
		{
		//	printf("fd in or out not valid\n");
			toex = toex->next;
			i++;
			continue ; // muss break sein sonst test 77 fehlerhaft cat < missing | cat
		}
		if (!toex->cmd)
		{
			toex = toex->next;
			i++;
			continue ;
		}
		if (builtin_check(toex->cmd) == 1 && !toex->next)
		{
		//	printf("builtin check erfolgreich cmd\n checkt %s\n", toex->cmd);
			if (which_builtin_parent(shell, toex->cmd, shell->toex->argv) != 0)
			{
				free_pipes(shell);
				free (shell->pids);
				shell->pids = NULL;
			//	free (shell->fd);
				return (1);
			}
		}
		else
		{
		//	printf("letzter cmd\n checkt %s\n", toex->cmd);
			if (exe_env(shell, shell->pids, i, toex) != 0)
			{
				perror("exe error\n");
				g_estatus = 1;
				return (1);
			}
		}
		toex = toex->next;
		i++;
	}
	wait_for_children(shell); //hier wird g_estatus ueberschrieben ob prozess erfolgreich oder nciht
	free_pipes(shell);
	free (shell->pids);
	shell->pids = NULL;
//	free (shell->fd); //problematic double free if its null noch protecten
	return(0);
}

int		valid_fd_in_out_check(t_command *toex)
{
	if(toex->fd_in == -1 || toex->fd_out == -1)
	{
		g_estatus = 1;
		return (1);
	}
	return (0);
}
