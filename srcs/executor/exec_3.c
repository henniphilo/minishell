#include "../../incl/minishell.h"


int		count_commands(t_data *shell)
{
	int		cmd_count;

	cmd_count = 0;
	while (shell->arguments[cmd_count] != NULL)
		cmd_count++;
	printf("command count is: %d\n", cmd_count);
	return(cmd_count);
}
static void	init_fd(t_data *shell)
{
	shell->fd = NULL;
}

int	execute_shell(t_data *shell)
{
	pid_t	pid;
	int		cmd_count;
	int		i;
	// if (pipe(fd) < 0)
	// 	perror("Error\n");
	i = 0;
	cmd_count = count_commands(shell);
	builtin_check(shell);
	init_fd(shell);
	while(cmd_count > 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork problem");
		}
		if (pid == 0) //ist in child
		{
			child_process_env(shell->arguments[i], shell);
		}
		else
		{
			//parent process
			printf("Elternprozess: PID = %d, Kindprozess-PID = %d\n", getpid(), pid);
		}
		waitpid(pid, NULL, 0);
		i ++;
		cmd_count--;
	}
	// }
	// else
	// 	execute_pipes(shell);
	return (1);
}


void	child_process_env(char *arg, t_data *shell)
{
	int		file_in;
	int		file_out;

	//file_in = open(arg , O_RDONLY, 0777);
	file_in  = dup(STDIN_FILENO);
	file_out = dup(STDOUT_FILENO);
	if (file_in == -1)
	{
		perror("error im child\n");
		exit(1);
	}
	printf("sind im child process\n");
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

