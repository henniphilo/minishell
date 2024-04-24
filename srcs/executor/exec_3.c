#include "../../incl/minishell.h"


int		count_commands(t_data *shell)
{
	int		cmd_count;

	cmd_count = 0;
	while (shell->arguments[cmd_count] != NULL)
		cmd_count++;
	//printf("command count is: %d\n", cmd_count);
	return(cmd_count);
}
static void	init_fd(t_data *shell)
{
	shell->fd = NULL;
}

int	execute_shell(t_data *shell)
{
	int		i;
	pid_t	pid;

	i = 0;
	pid = 0;
	shell->cmd_count = count_commands(shell); // -1 then you hve numbers of pipes. wenn ein command andere funktion
	if(shell->cmd_count > 0)
	{
		if(builtin_check(shell->arguments[i]) != 1)
		{
			if(shell->cmd_count == 1)
				execute_one_envcmd(shell, pid);
			else
			{
			//	while(shell->cmd_count > 1)
				execute_more_envcmd(shell, pid, i);
			}
		}
		else
		{
			printf("im parent\n");
			if(builtin_check(shell->arguments[i]) == 0)
				which_builtin_parent(shell, shell->arguments[i]);
			//parent process
			printf("Elternprozess: PID = %d, Kindprozess-PID = %d\n", getpid(), pid);
		}
		i++;
		shell->cmd_count--;
		waitpid(pid, NULL, 0);
	}
	return (1);
}


void	child_process_env(char *arg, t_data *shell, int i)
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
	env_execute(shell, arg);
}

// checken ob builtin oder env
// keeping track of closing pipe

// int	execute_pipes(t_data *shell)
// {


// }

