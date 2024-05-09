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

static void	execute_command(t_data *shell)
{
	char	*cmd;
	char	*path;

	//cmd_count = count_commands(shell->tokens);
	cmd = shell->toex->cmd;
	path = path_finder(cmd, shell);
	if(!path)
	{
		free(cmd);
		perror("Error in Path\n");
		exit(1);
	}
	printf("will executen: %s\n", cmd);
	if(execve(path, shell->toex->argv, shell->env) < 0)
	{
			perror("command couldnt be executed\n");
			free(cmd);
			exit(-1);
	}
	free(cmd);
	free(path);
}

int		piping(t_data *shell)
{
	const char	*process;
	int			fd[2];
	int			pid;
	int			i;
	int			cmd_count;

	i = 0;
	cmd_count = count_commands(shell->tokens);
	if(cmd_count > 0)
	{
		process = "PARENT";
		//fd = ft_calloc(2, sizeof(int));
		if (pipe(fd) != 0)
		{
			perror ("Error creating pipe.\n");
			exit(-1);
		}
		pid = fork();
		if (pid == -1)
		{
			perror ("Error creating pipe.\n");
			exit(-1);
    	}
		else if (pid == 0)
		{
			process = "CHILD";
			dup2(fd[RDEND], 0); /*Replace standard input of child process with read end of the pipe*/
			close(fd[WREND]); /* Close the write end of the pipe in child process.It is not used */
			close(fd[RDEND]); /* Close the read end of the pipe in child process.We have a copy of it in file descriptor 0*/
			//create a new pipe for chaining the next two commands
		//	fd = ft_calloc(2, sizeof(int));
		//	pipe(fd);
			execute_command(shell);
		//	exit(0);
		}
		else
		{
			//parent
			dup2(fd[WREND], 1); /*Replace standard output of parent process with write end of the pipe*/
			close(fd[RDEND]); /* Close the read end of the pipe in parent process.It is not used */
			close(fd[WREND]);/* Close the write end of the pipe in child process.We have a copy of it in file descriptor 1*/
			close(RDEND); /* After writing all data, close the write end */
			execute_command(shell);
			waitpid(pid, 0, 0); /* Wait for the child to finish */
		}
			cmd_count--;
		//i++;
	}
	return(1);
}


/*
char	**split_input_at_pipe(const char *line)
{
	char	**split_line;
	char	pipe;
	int		i;

	pipe = '|';
	i = 0;
	split_line = NULL;
	if(line == NULL)
	{
		perror("line error\n");
		exit (0);
	}
	while(line[i] != '\0')
	{
		if(line[i] == '|')
		{
			split_line = ft_split(line, pipe);
			return (split_line);
		}
		i++;
	}
	split_line = no_pipe(line);
	return (split_line);
}


char	**split_pipe_in_cmd(const char *split_line)
{
	printf("wir versuchen in cmds zu splitten\n");
	char	**command;
	char	space;
	int		i;

	space = ' ';
	i = 0;
	command = NULL;
	if(split_line == NULL)
	{
		perror("command split error\n");
		exit (0);
	}
	while(split_line[i] != '\0')
	{
		if(split_line[i] == ' ')
		{
			command = ft_split(split_line, space);
			return (command);
		}
		i++;
	}
	command = no_pipe(split_line);
	return (command);
}

char	**no_pipe(const char *line)
{
	char	**wo_split;
	int		len;

	if(line == NULL)
		exit(0);
	len = ft_strlen(line);
	wo_split = (char**)malloc(sizeof(wo_split) * len);
	wo_split[0] = ft_strdup((char *)line);
	wo_split[1] = NULL;
	return(wo_split);
}

void	space_toex(t_data *shell, char **toex)
{
	int		i;

	i = 0;
	while(toex[i] != NULL)
	{
		i++;
	}
	shell->toex = (char **)ft_calloc(sizeof(toex) * i, sizeof(char));
}
*/
/*
static char	*line_trim(const char *line)
{
	//ausdehnen auf alle white spaces
	const char	*set;
	char	*trim;

	set = " ";
	trim = ft_strtrim(line, set);

	return(trim);
}
*/
/*
void	init_args(t_data *shell, char **split)
{
	int		i;

	i = 0;

	space_args(shell, split);

	while(split[i] != NULL)
	{
		split[i] = line_trim(split[i]);
		shell->arguments[i] = ft_strdup(split[i]);
		printf("xasdadargs[%d]: %s\n",i, shell->arguments[i]);
		free (split[i]);
		i++;
	}
	free(split[i]);
	shell->arguments[i] = NULL;
	// printf("args[%d]: %s\n",i, shell->arguments[i]);
	count_commands(shell);
}
*/

//zeites array mit meinen commands, dann dreifach array was auf die anderen arrays pointet mit arguments and executables
// zweimal splitten erster command erst mnach pipes schauen dann nach commands

/*
void	space_cmds(t_data *shell, char **cmds)
{
	int		i;

	i = 0;
	while(cmds[i] != NULL)
	{
		i++;
	}
	shell->cmds = (char **)ft_calloc(sizeof(cmds) * i, sizeof(char));
}

void	init_cmds(t_data *shell, char **pipeline)
{
	int		i;

	i = 0;

	space_cmds(shell, pipeline);

	while(pipeline[i] != NULL)
	{
		pipeline[i] = line_trim(pipeline[i]);
		shell->cmds[i] = ft_strdup(pipeline[i]);
		printf("cmds[%d]: %s\n",i, shell->cmds[i]);
		free (pipeline[i]);
		i++;
	}
	free(pipeline[i]);
	shell->cmds[i] = NULL;
	printf("cmds[%d]: %s\n",i, shell->cmds[i]);
} */
