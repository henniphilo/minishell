#include "../incl/minishell.h"

int	g_estatus;

void	print_toex(t_data *shell)
{
	int		i;

	i = 0;
	if(shell->toex->cmd != NULL)
		printf("cmd is: %s\n", shell->toex->cmd);

	while(shell->toex->args != NULL && shell->toex->args[i])
	{
		printf("arg[%d] is: %s\n", i, shell->toex->args[i]);
		i++;
	}
}


int	main(int ac, char **av, char **envp)
{
	t_data		*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL, 1);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL, 1);
	init_env(shell, envp); //make init function
	while(1)
	{
		shell->buf = (char *)get_the_line(shell);
		if (check_line(shell->buf) || lexer(shell) || parser(shell))
		{
			clear_data(shell);
			continue ; //if lexing, parsing or line are wrong returns the prompt
		}
	//	test(shell);
	//	execute_shell(shell);
	//	piping(shell);
		if ((pipeline_exe(shell) != 0))
			perror("Error in Execution\n");
		clear_data(shell);
	}

}
