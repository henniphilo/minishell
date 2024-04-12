#include "../incl/minishell.h"

const char	*get_the_line(t_data *data)
{
	const char	*line;

	line = readline("our minishell 🌺: ");
	if (!line)
		panic(RL_ERR, data);
	add_history(line);
	return (line);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 1 || !av)
		panic(ARG_ERR, NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR, NULL);
	init_data(data); //make init function
	data->env = environ;
	while (1)
	{
		data->buf = get_the_line(data);
		printf("%s", data->buf); //test
		int i = -1;
		while (data->env[++i])
			printf("%s", data->env[i]); //test
		//lex();
		//parse();
		//arguments = split_input(line);
		//execution
		//free(arguments);
	}
	return (0);
}
