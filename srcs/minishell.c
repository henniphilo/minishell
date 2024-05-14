#include "../incl/minishell.h"

int	g_estatus;

int	main(int ac, char **av, char **envp)
{
	t_data		*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL, 1);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL, 1);
	init_env(shell, envp);
	//handle_signal();
	int i = 0; //test
	while (i < 1)
	{
		shell->buf = (char *)get_the_line(shell);
		if (check_line(shell->buf) || lexer(shell) || parser(shell))
		{
			clear_data(shell);
			continue ; //if lexing, parsing, or input are wrong, returns the prompt
		}
		//execute_shell(shell);
		test(shell);
		clear_data(shell);
		i++; //test
	}
	free_data(shell); //just temporarily in this part of the code
	return (0);
}
