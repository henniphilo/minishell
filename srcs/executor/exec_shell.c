#include "../../incl/minishell.h"

int	execute_shell(t_data *shell)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	shell->cmd_count = count_commands(shell->toex);
	if(shell->cmd_count > 0)
	{
		if(builtin_check(shell->toex->cmd) != 1)
		{
			printf("-toex zwischen check -\n");
			print_toex(shell);
			printf("-toex zwischen check ende -\n");

			if(shell->cmd_count == 1)
				execute_one_envcmd(shell, pid); //soll nicht unbedingt in child wenn nur ein cmd
			else
				execute_more_envcmd(shell, pid, i);
		}
		else
		{
			printf("im parent\n");
			if(builtin_check(shell->toex->cmd) == 1)
			{
				printf("checkt jetzt builtin bei toex[%d]:%s\n", i, shell->toex->cmd);
				which_builtin_parent(shell, shell->toex->cmd);
			}
		//	printf("parent: PID = %d, child-PID = %d\n", getpid(), pid);
		}
		i++;
		shell->cmd_count--;
		waitpid(pid, NULL, 0);
	}
	return (1);
}

// checken ob builtin oder env
// keeping track of closing pipe
/*
void	print_cmds(t_data *shell)
{
	int	i;

	i = 0;
	while(shell->cmds != NULL)
	{
		printf("cmds[%d]: %s\n",i, shell->cmds[i]);
		i++;
	}
} */
