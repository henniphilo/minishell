#include "../../incl/minishell.h"

int	builtin_check(char *arg)
{
	int	n;

	n = 7;

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
