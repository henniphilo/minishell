#include "../../incl/minishell.h"


void		count_commands(t_data *shell)
{
	printf("hi we are in count cmd\n");
	int		cmd_count;
	int		i;

	i = 0;
	cmd_count = 0;
	while (shell->cmds[cmd_count] != NULL) //eigentlich gerade ein pipe count
		cmd_count++;
	// if(cmd_count >= 1)
	// {
	// 	while(i < cmd_count)
	// 	{
	// 		printf("in c_count is arg[%d]: %s\n", i, shell->arguments[i]);
	// 		shell->cmds = split_pipe_in_cmd(shell->arguments[i]);
	// 		//shell->cmds = ft_split(shell->arguments[i], ' ');
	// 		i++;
	// 	}
	// }
	shell->cmd_count = cmd_count; // -1 then you hve numbers of pipes
	printf("count is: %d\n", shell->cmd_count);
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
	if(shell->cmd_count > 0)
	{
		if(builtin_check(shell->cmds[i]) != 1)
		{
			if(shell->cmd_count == 1)
				execute_one_envcmd(shell, pid); //soll nicht unbedingt in child wenn nur ein cmd
			else
				execute_more_envcmd(shell, pid, i);
		}
		else
		{
			printf("im parent\n");
			if(builtin_check(shell->cmds[i]) == 0)
				which_builtin_parent(shell, shell->cmds[i]);
		//	printf("parent: PID = %d, child-PID = %d\n", getpid(), pid);
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

void	print_cmds(t_data *shell)
{
	int	i;

	i = 0;
	while(shell->cmds != NULL)
	{
		printf("cmds[%d]: %s\n",i, shell->cmds[i]);
		i++;
	}
}
