#include "../incl/minishell.h"

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
}


char	**split_input(const char *line)
{
	char	**split_line;
	char	pipe;

	pipe = '|';
	split_line = ft_split(line, pipe);

	return (split_line);
}

static void	space_args(t_data *shell, char **args)
{
	int		i;

	i = 0;
	while(args[i] != NULL)
	{
		i++;
	}
	shell->arguments = (char **)malloc(sizeof(args) * i);
}

void	init_args(char **split)
{
	int		i;
	t_data	shell;

	i = 0;

	space_args(&shell, split);

	while (split[i])
	{
		shell.arguments[i] = split[i];
		printf("%s\n", shell.arguments[i]);
		free (split[i]);
		i++;
	}
}
//hier weiternachen
int	launch_shell(t_data *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork problem");
	}
	if (pid == 0)
		execute ();
		//to be continued
}



