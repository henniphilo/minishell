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

/*function to free buffer and parsing + lexing structures before reentering the loop*/
void	clear_data(t_data *data)
{
	if (data->buf)
	{
		free(data->buf);
		data->buf = NULL;
	}
	free_tokens(&(data->tokens));
	data->tokens = NULL;
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
	while (++i < 3) //test
	{
		data->buf = (char *)get_the_line(data);
		//data->arguments = split_input(data->buf);
		//init_args(data, data->arguments);
		if (check_line(data->buf) || lexer(data))
			continue ; //if lexing, parsing or line are wrong returns the prompt
		//execute_shell(data);
		clear_data(data);
	}
	free_data(data); //just temporarily in this part of the code
	return (0);
}
