#include "../../incl/minishell.h"

int	builtin_check(char *arg)
{
	int	n;

	n = 7;

	if((ft_strncmp((const char *)arg, "cd", n) == 0)
		|| (ft_strncmp((const char *)arg, "exit", n) == 0)
		|| (ft_strncmp((const char *)arg, "unset", n) == 0)
		|| (ft_strncmp((const char *)arg, "pwd", n) == 0)
		|| (ft_strncmp((const char *)arg, "export", n) == 0))
	{
		printf("is a builtin in parent \n");
		return(1);
	}
	return (0);
}

void	which_builtin_parent(t_data *shell, char *arg)
{
	int	n;

	n = 7;
	shell->bi_check = 1;
	if(ft_strncmp((const char *)arg, "cd", n) == 0)
	{
		if(change_directory(shell) != 0)
			perror("error in cd\n");
	}
	if(ft_strncmp((const char *)arg, "export", n) == 0)
	{
		bi_export(shell);
	}
	if(ft_strncmp((const char *)arg, "pwd", n) == 0)
	{
		bi_pwd();
	}
	if(ft_strncmp((const char *)arg, "unset", n) == 0)
	{
		bi_unset(shell);
	}
	if(ft_strncmp((const char *)arg, "exit", n) == 0)
	{
		bi_exit(shell);
	}
}
//here toex[1] als placeholder
//noch cd .. klaeren
int	change_directory(t_data *shell)
{
	char	*new_path;
	char	*current_path;
	char	*home_path;

	current_path = find_in_env("PWD");
	home_path = find_in_env("HOME");
	printf("start ");
	print_path(current_path);
	printf("Home ");
	print_path(home_path);
	if(shell->toex[1] == NULL) //here aendern fuer ..
	{
		printf("going home\n");
		chdir(home_path);
		return(0);
	}
	new_path = path_finder(shell->toex[1], shell);
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
	return(1);
}

void	bi_exit(t_data *shell)
{
	free_data(shell); //hier noch memory leaks bei space_toex
	exit(0);
}

void	bi_pwd()
{
	char	*current_path;

	current_path = find_in_env("PWD");
	printf("%s\n", current_path);
}
