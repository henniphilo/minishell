#include "../../incl/minishell.h"




void	execute_one_envcmd(t_data *shell, pid_t pid)
{
	printf("ein toex\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork problem");
		exit (1);
	}
	if (pid == 0)
	{
	//	printf("count: %d & i: %d\n", cmd_count, i);
		if((which_builtin_child(shell, shell->toex->cmd))== 1)
			child_process_env(shell->toex->cmd, shell, 0);
	}
}

// -> macht nicht so viel sinn weil nur ein ausfuehrbarer command
void	execute_more_envcmd(t_data *shell, pid_t pid, int i)
{
	printf("mehrere toex\n");
	pid = fork();
	if (pid < 0)
	{
		perror("fork problem");
		exit (1);
	}
	if (pid == 0)
	{
		printf("count: %d & i: %d\n", shell->cmd_count, i);
		if((which_builtin_child(shell, shell->toex->cmd))== 1)
			child_process_env(shell->toex->cmd, shell, i);
	}
}

static void	init_fd(t_data *shell)
{
	shell->fd = NULL;
}

void	child_process_env(char *toex, t_data *shell, int i)
{
	int		file_in;
	int		file_out;

	init_fd(shell); //wahrscheinlich hier fehler ->  nutze ich noch gar nicht
	file_in  = (dup(STDIN_FILENO) + i);
	file_out = (dup(STDOUT_FILENO) + i);
	if (file_in == -1)
	{
		perror("error im child\n");
		exit(1);
	}
	printf("sind im child process\n");
	printf("file in: %d & file out %d \n", file_in, file_out);
	dup2(file_out, STDOUT_FILENO);
	dup2(file_in, STDIN_FILENO); // siehe pipex notes and beispiel von flo in new
	close(file_in);
	close(file_out);
	env_execute(shell, toex);
}
