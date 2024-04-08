#include "../incl/minishell.h"

const char	*read_the_line()
{
	const char	*line;

	line = readline("our minishell 🌺: ");
	// if(!line)
	// {
	// 	perror("rl_error\n");
	// 	exit(1);
	// }
	return(line);
}


char	**split_input(const char *line) //umwandeln in char **arguments zum executen
{
	char	**split_line;
	char	pipe;
	int		i;

	pipe = '|';
	while (1)
	{
		split_line = ft_split(line, pipe);
		// noch saven
		i = 0;
		while (split_line[i])
		{
			ft_printf("%s\n", split_line[i]);
		//	free(split_line[i]);
			i++;
		}
		//free(split_line);
		//free(line);
	}
	return (split_line);
}
