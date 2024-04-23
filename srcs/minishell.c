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

// static void	envp_care(t_data *shell, char **envp)
// {
// 	int		i;

// 	i = 0;
// 	while(envp[i] != NULL)
// 	{
// 		i++;
// 	}
// 	shell->env = (char **)malloc(sizeof(envp) * i);
// 	shell->env = envp;
// }

/*function to free buffer and parsing + lexing structures before reentering the loop*/
void	clear_data(t_data *data)
{
	if (data->buf)
	{
		free(data->buf);
		data->buf = NULL;
	}
	free_tokens(&(data->tokens));
}

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	int	i; //test

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR, NULL);
	init_data(data, envp); //make init function
	i = 0; //test
	while (i < 2)
	{
		data->buf = (char *)get_the_line(data);
		//data->arguments = split_input(data->buf);
		//init_args(data, data->arguments);
		if (check_line(data->buf) || lexer(data))
			continue ;
		//execute_shell(data);
		clear_data(data);
		i++; //test
	}
	free_data(data); //just temporarily in this part of the code
	return (0);
}
