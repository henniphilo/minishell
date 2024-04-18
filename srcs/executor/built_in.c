#include "../../incl/minishell.h"

static void	builtin_init(t_data *shell)
{
	shell->bi = malloc(sizeof(t_builtin));
	if(shell->bi == NULL)
	{
		perror("malloc errror builtins \n");
		exit(1);
	}
	shell->bi->cd = "cd";
	shell->bi->echo= "echo";
	shell->bi->alias = "alias";
	shell->bi->export = "export";
	shell->bi->unset = "unset";
	shell->bi->source = "source";
	shell->bi->exit = "exit";
	shell->bi->env = "env";
}


int	builtin_check(t_data *shell)
{
	int	i;
	int	n;

	i = 0;
	n = 7;
	builtin_init(shell);
	while(shell->arguments[i] != NULL)
	{
		if((ft_strncmp((const char *)shell->arguments[i], shell->bi->cd, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->echo, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->alias, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->export, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->unset, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->source, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->exit, n) == 0)
			|| (ft_strncmp((const char *)shell->arguments[i], shell->bi->env, n) == 0))
		{
			printf("is a built in \n");
			return(1);
		}
		i++;
	}
	return (0);
}
