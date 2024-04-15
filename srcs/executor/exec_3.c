#include "../../incl/minishell.h"


//hier weiternachen
int	launch_shell(t_data *shell)
{
	pid_t	pid;

	// if (pipe(fd) < 0)
	// 	perror("Error\n");

	pid = fork();

	if (pid < 0)
	{
		perror("fork problem");
	}
	if (pid == 0) //ist in child
		execute (shell, shell->env);
	else
	{
		//parent process
		printf("Elternprozess: PID = %d, Kindprozess-PID = %d\n", getpid(), pid);
	}
	waitpid(pid, NULL, 0);

	return (1);
}
