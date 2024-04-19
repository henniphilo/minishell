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


int	builtin_check(t_data *shell, char *arg)
{

	int	n;

	n = 7;
	builtin_init(shell);
	if((ft_strncmp((const char *)arg, shell->bi->cd, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->echo, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->alias, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->export, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->unset, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->source, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->exit, n) == 0)
		|| (ft_strncmp((const char *)arg, shell->bi->env, n) == 0))
	{
		printf("is a built in \n");
		return(1);
	}
	return (0);
}

void	when_builtin(t_data *shell)
{
	// hier ausbauen und builtin action zusammen fuehren
	printf("approved builtin is: %s\n", shell->bi);
}
