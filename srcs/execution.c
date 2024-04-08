#include "../minishell.h"

char	read_the_line()
{
	char	*line;

	line = readline("our minishell 🌺: ");
	if(!line)
	{
		perror("rl_error\n");
		exit(1);
	}
	return(line);
}


int	split_input(char *line) //umwandeln in char **arguments zum executen
{
	char	**split_line;
	char	pipe;
	int		i;

	pipe = '|';
	while (1)
	{
		split_line = ft_split(line, pipe);
		if(!split_line)
			{
				perror("split error\n");
				return (1);
			}
		i = 0;
		while (split_line[i])
		{
			ft_printf("%s\n", split_line[i]);
			free(split_line[i]);
			i++;
		}
		free(split_line);
		free(line);
	}
	return (0);
}
