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
	if(shell->toex->cmd != NULL)
		printf("cmd is: %s\n", shell->toex->cmd);

	while(shell->toex->args != NULL)
	{
		printf("arg[%d] is: %s\n", i, shell->toex->args[i]);
		i++;
	}
	printf("last toex[%d] is: %s\n", i, shell->toex->args[i]);
}


int	main(int ac, char **av, char **envp)
{
	t_data		*shell;

	if (ac != 1 || !av[0])
		panic(ARG_ERR, NULL);
	shell = ft_calloc(1, sizeof(t_data));
	if (!shell)
		panic(ALLOC_ERR, NULL);
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
	//	hard_toex(shell);
		count_commands(shell->tokens);
	//	print_toex(shell);
		execute_shell(shell);
		clear_data(shell);
	}

}
/*
void	hard_pipeline(t_data *shell)
{
//	space_pipeline(shell, (char***)shell->buf);
	shell->pipeline = (char***)(ft_split(shell->toex, '|'));
	if(!shell->pipeline)
		shell->pipeline = (char***)shell->buf;
//	print_pipeline(shell);
}
*/





//hier ersetzen von petra -----> hab ich von char **toex in t_command *toex geaendert
/*
void	hard_toex(t_data *shell)
{
	space_toex(shell, &shell->buf);
	shell->toex = ft_split(shell->buf, ' ');
	if(!shell->toex)
		shell->toex = &shell->buf;
} */
/*
void	hard_toex(t_data *shell) //wenn ***pipeline funktioniert
{
	int		i;

	i = 0;
	while(shell->pipeline[i] != NULL)
	{
		space_toex(shell, shell->pipeline[i]);
		shell->toex = ft_split(*(shell->pipeline[i]), ' ');
		i++;
	}
	if(!shell->toex)
		shell->toex = &shell->buf;
}*/
