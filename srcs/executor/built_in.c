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
		if(change_directory(shell) != 0)
			perror("error in cd\n");
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
//here toex[1] als placeholder und currentpath ueberdenken
//also erstmal momentanes pwd bekommen, damit dieses dann oldpwd werden kann
//in env nach HOME= suchen
int	change_directory(t_data *shell)
{
	char	*new_path;
	char	*current_path;

	current_path = "/start_minishell/minishell"; //funktioniert noch nicht
	printf("start ");
	print_path(current_path);
	new_path = path_finder(shell->toex[1], shell->env);
	if(new_path != NULL)
	{
		printf("geht zu neuem ");
		print_path(new_path);
		if(chdir(new_path) == 0)
		{
			printf("changes directory\n");
			return(0);
		}
	}
	else
		chdir(current_path);
	return(1);
}

char	*new_path()



void	when_builtin(t_data *shell)
{
	printf("arg0 %s\n", shell->toex[0]);
	// wird gerade auch noch ausgeführt wenn einfach nur im parent
	// hier ausbauen und builtin action zusammen fuehren
	printf("approved builtin is: \n");
}
