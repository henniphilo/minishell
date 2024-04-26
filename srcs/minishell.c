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

int	main(int ac, char **av, char **envp)
{
	t_data		*data;
	int			i;
	int			j;
	int			k;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		panic(ALLOC_ERR, NULL);
	init_data(data, envp); //make init function
	while (1)
	{
		i = 0;
		j = 0;
		k = 0;
		// data = smth() ->
		data->buf = (char *)get_the_line(data);
		//data->arguments = split_input_at_pipe(data->buf);
		space_args(data, &data->buf);
		if(!(data->arguments = ft_split(data->buf, '|')))
			data->arguments = &data->buf;
		while(data->arguments[k] != NULL)
			{
				printf("new data->args[%d] %s\n", k, data->arguments[k]);
				k++;
			}
		space_cmds(data, data->arguments);
		//nathan says hard coding the arguments and not caring about parsing stuff
		data->cmds = calloc(6000, 1);
		data->cmds[0] = strdup("ls -la");
	//	data->cmds[1] = strdup("pwd");
		//while(data->arguments[i] != NULL)
		//{
		//	data->cmds = ft_split(data->arguments[i], 32);
		//	while(data->cmds[j] != NULL)
		//	{
		//		printf("new data->cmds[%d] %s\n", j, data->cmds[j]);
		//		j++;
		//	}
		//	i++;
		while (data->env[++i]) //test
			printf("%s\n", data->env[i]); //test
		panic("exited", data); //test */

		/* printf("%s\n", data->buf); //test */

		//check_input()
		//lex();
		//parse();
		//arguments = split_input(line);
		//execution
		//free(arguments);
	}
	return (0);
}
