#include "../incl/minishell.h"

int	g_estatus = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL, 1);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL, 1);
	init_env(shell, envp);
	while (1)
	{
		handle_signals();
		shell->buf = (char *)get_the_line(shell);
		handle_signals_children();
		if (check_line(shell->buf) || lexer(shell) || parser(shell))
		{
			clear_data(shell);
			continue ;
		}
//		test(shell);
		if ((pipeline_exe(shell) != 0))
			error_int(EXEC_ERR);
		clear_data(shell);
	}
	return (0);
}
