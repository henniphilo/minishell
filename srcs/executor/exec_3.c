#include "../../incl/minishell.h"


int		count_commands(t_data *shell)
{
	int		cmd_count;

	cmd_count = 0;
	while (shell->arguments[cmd_count] != NULL)
		cmd_count++;
	printf("command count is: %d\n");
	return(cmd_count);
}


//hier weiternachen
int	execute_shell(t_data *shell)
{
	pid_t	pid;
	int		cmd_count;

	// if (pipe(fd) < 0)
	// 	perror("Error\n");
	cmd_count = count_commands(shell);
	if(cmd_count == 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork problem");
		}
		if (pid == 0) //ist in child
			env_execute (shell, shell->env);
		else
		{
			//parent process
			printf("Elternprozess: PID = %d, Kindprozess-PID = %d\n", getpid(), pid);
		}
		waitpid(pid, NULL, 0);
	}
	else
		execute_pipes(shell);
	return (1);
}

int	execute_pipes(t_data *shell)
{
	
}

