#include "../../incl/minishell.h"

int	execute_shell(t_data *shell)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	shell->cmd_count = count_commands(shell->tokens);
//	printf("command count is: %d\n", shell->cmd_count);
	if(shell->cmd_count > 0)
	{
		if(builtin_check(shell->toex->cmd) != 1)
		{
			// printf("-toex zwischen check -\n");
			// print_toex(shell);
			// printf("-toex zwischen check ende -\n");
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

/*
int	execute_shell(t_data *shell)
{
	int		i;
	int		pipefd[2];
	pid_t	pid;

	i = 0;
	pid = 0;
	shell->cmd_count = count_commands(shell->tokens);
	if(shell->cmd_count > 0)
	{
		if(builtin_check(shell->toex->cmd) != 1)
		{
			while(shell->cmd_count >= 1)
			{
				if(pipe(pipefd) == -1)
					perror("pipe error\n");
				pid = fork();
				if (pid < 0)
				{
					perror("fork problem");
					exit (1);
				}
				if (pid == 0)
				{
					if((which_builtin_child(shell, shell->toex->cmd))== 1)
						child_process_env(shell->toex->cmd, shell, i);
				}
				parent_process();

				shell->cmd_count--;
				i++;
			}
		}
		else
		{
			if(builtin_check(shell->toex->cmd) == 1)
				which_builtin_parent(shell, shell->toex->cmd);
		}
		waitpid(pid, NULL, 0);
	}
	return (1);
} */

