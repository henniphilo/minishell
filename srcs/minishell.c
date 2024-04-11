#include "../incl/minishell.h"

extern char	**environ; //better than envp?

const char	*read_the_line()
{
	const char	*line;

	line = readline("our minishell 🌺: ");
	if(!line)
		panic(RL_ERR);
	add_history(line);
	return(line);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 1)
		panic(ARG_ERR);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR);
	init(data); //make init function
	data->env = environ;
	while (1)
	{
		data->buf = read_the_line();
		parse_line();
		//arguments = split_input(line);

		//execution

		//free(arguments);
	}
	return (0);
}
