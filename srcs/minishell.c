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

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR, NULL);
	init_data(data, envp); //make init function
	while (1)
	{
		data->buf = (char *)get_the_line(data);
		/* printf("%s\n", data->buf); //test
		int i = -1; //test
		while (data->env[++i]) //test
			printf("%s\n", data->env[i]); //test
		panic("exited", data); //test */
		//check_input()
		//lex();
		//parse();
		//arguments = split_input(line);
		//execution
		//free(arguments);
	}
	return (0);
}
