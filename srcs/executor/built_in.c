#include "../../incl/minishell.h"
/*
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
} */


int	builtin_check(char *arg)
{
	int	n;

	n = 7;
	//builtin_init(shell);

	if((ft_strncmp((const char *)arg, "cd", n) == 0)
		|| (ft_strncmp((const char *)arg, "exit", n) == 0)
		|| (ft_strncmp((const char *)arg, "unset", n) == 0)
		|| (ft_strncmp((const char *)arg, "export", n) == 0))
	{
		printf("is a builtin in parent \n");
		return(1);
	}
	return (0);
}

int	which_builtin_child(t_data *shell, char *arg)
{
	int	n;

	n = 7;
	shell->bi_check = 1;
	if(ft_strncmp((const char *)arg, "alias", n) == 0) //wahrscheinlich nicht laut jan
	{
		printf("its alias\n");
		return(0);
	}
	if(ft_strncmp((const char *)arg, "source", n) == 0) //wahrscheinlich nicht laut jan
	{
		printf("its source\n");
		return(0);

	}
	if(ft_strncmp((const char *)arg, "env", n) == 0)
	{
		printf("its env\n");
		return(0);
	}
	if(ft_strncmp((const char *)arg, "echo", n) == 0)
	{
		printf("its echo\n");
		return(0);
	}
	return(1);
}

void	which_builtin_parent(t_data *shell, char *arg)
{
	int	n;

	n = 7;
	shell->bi_check = 1;
	if(ft_strncmp((const char *)arg, "cd", n) == 0)
	{
		printf("its cd\n");
	}
	if(ft_strncmp((const char *)arg, "export", n) == 0)
	{
		printf("its export\n");

	}
	if(ft_strncmp((const char *)arg, "unset", n) == 0)
	{
		printf("its unset\n");

	}
	if(ft_strncmp((const char *)arg, "exit", n) == 0)
	{
		printf("its exit\n");
	}
}


void	when_builtin(t_data *shell)
{
	printf("arg0 %s\n", shell->toex[0]);
	// wird gerade auch noch ausgeführt wenn einfach nur im parent
	// hier ausbauen und builtin action zusammen fuehren
	printf("approved builtin is: \n");
}
