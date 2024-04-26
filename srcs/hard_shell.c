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

void	print_toex(t_data *shell)
{
	int		i;

	i = 0;
	while(shell->toex[i] != NULL)
	{
		printf("toex[%d] is: %s\n", i, shell->toex[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data		*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL);
	init_data(shell, envp); //make init function
	while(1)
	{
		shell->buf = (char *)get_the_line(shell);
		hard_toex(shell);
		print_toex(shell);
		count_commands(shell);
		execute_shell(shell);


	}

}

void	hard_toex(t_data *shell)
{
	space_toex(shell, &shell->buf);
	shell->toex = ft_split(shell->buf, ' ');
	if(!shell->toex)
		shell->toex = &shell->buf;
}
