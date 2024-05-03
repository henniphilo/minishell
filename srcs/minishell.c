#include "../incl/minishell.h"

const char	*get_the_line(t_data *shell)
{
	const char	*line;

	line = readline("our minishell 🌺: ");
	if (!line)
		panic(RL_ERR, shell);
	add_history(line);
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	t_data		*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL);
	init_env(shell, envp);
	int i;
	i = 0;
	while (i < 1)
	{
		shell->buf = (char *)get_the_line(shell);
		if (check_line(shell->buf) || lexer(shell) || parser(shell))
		{
			//if (shell->tokens)
				//parse_heredocs();
			clear_data(shell);
			continue ; //if lexing, parsing or input are wrong, returns the prompt
		}
		//execute_shell(shell);
		test(shell);
		clear_data(shell);
		i++;
	}
	free_data(shell); //just temporarily in this part of the code
	return (0);
}
