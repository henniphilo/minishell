#include "../../incl/minishell.h"


void	execute_one_envcmd(t_data *shell, pid_t pid)
{
	printf("ein cmd\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork problem");
		exit (1);
	}
	if (pid == 0)
	{
	//	printf("count: %d & i: %d\n", cmd_count, i);
		if((which_builtin_child(shell, shell->arguments[0]))== 1)
			child_process_env(shell->arguments[0], shell, 0);
	}
}
void	execute_more_envcmd(t_data *shell, pid_t pid, int i)
{
	printf("mehrere cmd\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork problem");
		exit (1);
	}
	if (pid == 0)
	{
		printf("count: %d & i: %d\n", shell->cmd_count, i);
		if((which_builtin_child(shell, shell->arguments[i]))== 1)
			child_process_env(shell->arguments[i], shell, i);
	}
}
