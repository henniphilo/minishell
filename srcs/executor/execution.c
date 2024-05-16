#include "../../incl/minishell.h"

void read_from_fd(int fd, const char *process)
{
    char c;

    printf ("Process [%s] Reading from descriptor %d \n", process, fd);
    while(read(fd, &c, 1) != 0)
	{
        printf("%c", c);
    }
}

static int	execute_command(t_data *shell, t_command *toex)
{
	char	*path;

	path = path_finder(toex->cmd, shell);
	if(!path)
	{
		free(toex->cmd);
		perror("Error in Path\n");
		exit(1);
	}
//	printf("will executen: %s\n", toex->cmd);
	if(execve(path, toex->argv, shell->env) < 0)
	{
		perror("command couldnt be executed\n");
		free(toex->cmd);
		return (1);
	}
	free(toex->cmd);
	free(path);
	return (0);
}

int		**creating_pipes(t_data *shell)
{
	int		**piped_fd;
	int		i;

	i = 0;
	piped_fd = (int**) ft_calloc(shell->cmd_count, sizeof(int *));
	if(!piped_fd)
	{
		perror("could not create pipe\n");
		return (NULL);
	}
	while(i < shell->cmd_count - 1)
	{
		piped_fd[i] = (int *) ft_calloc(2, sizeof(int));
		if (pipe(piped_fd[i]) == -1)
		{
			perror("pipe error");
			while (i >= 0)
				free(piped_fd[i--]);
			free(piped_fd);
			return (NULL);
		}
		i++;
	}
	return (piped_fd);
}

static void	init_fd(t_data *shell)
{
	shell->fd = NULL;
}

// static void		print_fd(t_data *shell)
// {
// 	int		j;

// 	j = 0;
// 	while(shell->fd && (j < (shell->cmd_count) - 1))
// 	{
// 		printf("shell fd %d\n", shell->fd[j][RDEND]);
// 		printf("shell fd %d\n", shell->fd[j][WREND]);
// 		j++;
// 	}
// }
void	init_pipeline(t_data *shell)
{
	shell->pids = (pid_t*) ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		perror("Error pid init\n");
		exit(EXIT_FAILURE);
	}
	init_fd(shell);
	if(shell->cmd_count > 1)
		shell->fd = creating_pipes(shell);
	//print_fd(shell);
}


int		pipeline_exe(t_data *shell)
{
	t_command	*toex;
	int			i;

	i = 0;
	toex = shell->toex;
	init_pipeline(shell);
	while(toex)
	{
		if (builtin_check(toex->cmd) == 1)
			which_builtin_parent(shell, toex->cmd);
		else
		{
			if (exe_env(shell, shell->pids, i, toex) == 1)
			{
				perror("exe Error\n");
				return (1);
			}
		}
		toex = toex->next;
		i++;
	}
	free (shell->fd); //problematic double free if its null noch protecten
	free (shell->pids);
	return(0);
}

void	child_process(t_data *shell, int i, t_command *toex)
{
	if (shell->cmd_count > 1)
		{
			if(i + 1 < shell->cmd_count)
			{
				if(dup2(shell->fd[i][WREND], STDOUT_FILENO) == -1)
				{
					perror("dup2 WREND\n");
					exit(EXIT_FAILURE);
				}
				close(shell->fd[i][RDEND]);
			}
			if(i > 0)
			{
				if(dup2(shell->fd[i - 1][RDEND], STDIN_FILENO) == -1)
				{
					perror("dup2 RDEND");
					exit(EXIT_FAILURE);
				}
				close(shell->fd[i - 1][WREND]);
				close(shell->fd[i - 1][RDEND]);
			}
			close_pipes(shell);
		}
		execution(shell, toex);
}

void	execution(t_data *shell, t_command *toex)
{
	if (which_builtin_child(shell, toex->cmd) != 0)
	{
		if (execute_command(shell, toex) != 0)
		{
			perror("Error executing command\n");
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

//ist nicht nur env checkt auch buildin -> umbenennen
int		exe_env(t_data *shell, pid_t *pids, int i, t_command *toex)
{
	pids[i] = fork();

	if (pids[i] < 0)
	{
		perror("fork error \n");
		return (1);
	}
	if (pids[i] == 0)
		child_process(shell, i, toex);
	else
	{
		if(i > 0)
		{
			close(shell->fd[i -1][WREND]);
			close(shell->fd[i - 1][RDEND]);
		}
		else if(shell->fd) //wenn es nur eine pipe gibt
			close(shell->fd[0][WREND]);
		waitpid(pids[i], 0, 0);
	}
	return (0);
}

void	close_pipes(t_data *shell)
{
	int		i;

	i = 0;
	while(i + 1 < shell->cmd_count)
	{
		close(shell->fd[i][WREND]);
		close(shell->fd[i][RDEND]);
		i++;
	}
}
