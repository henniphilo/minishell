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

int main()
{
	const char	*line;
	char	**arguments;
	//command loop

	while(1)
	{
		line = read_the_line();
		arguments = split_input(line);

		//execution

		free(arguments);
	}
	return (0);
}
