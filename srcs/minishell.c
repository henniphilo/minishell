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
	t_data		*data;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR, NULL);
	init_env(data, envp);
	int i = 0; //test
	while (++i < 2) //test
	{
		data->buf = (char *)get_the_line(data);
		//data->arguments = split_input(data->buf);
		//init_args(data, data->arguments);
		if (check_line(data->buf) || lexer(data) || parser(data))
		{
			clear_data(data);
			continue ; //if lexing, parsing or line are wrong returns the prompt
		}
		//execute_shell(data);
		test(data);
		clear_data(data);
	}
	free_data(data); //just temporarily in this part of the code
	return (0);
}
