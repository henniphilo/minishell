#include "../../incl/minishell.h"
/*
const char	*read_the_line()
{
	const char	*line;

	line = readline("our minishell 🌺: ");
	if(!line)
	{
		perror("rl_error\n");
		exit(1);
	}
	add_history(line);
	return(line);
} */


char	**split_input(const char *line)
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

static void	space_args(t_data *shell, char **args)
{
	int		i;

	i = 0;
	while(args[i] != NULL)
	{
		i++;
	}
	shell->arguments = (char **)ft_calloc(sizeof(args) * i, sizeof(char));
}

void	init_args(t_data *shell, char **split)
{
	int		i;

	i = 0;

	space_args(shell, split);
	while (split[i] != NULL)
	{
		shell->arguments[i] = ft_strdup(split[i]);
		printf("in  init_args geprintet: %s\n", shell->arguments[i]);
		free (split[i]);
		i++;
	}
	shell->arguments[i] = NULL;
}
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



