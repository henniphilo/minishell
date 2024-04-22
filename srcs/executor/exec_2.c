
#include "../../incl/minishell.h"

// static void	print_path(char *path)
// {
// //	printf("hi in print_path\n");
// 	if(path != NULL)
// 		printf("path: %s\n", path);
// }

char	*path_finder(char *cmd, char **envp)
{
	int	i;
	char	**path_components;
	char	*current_path;
	char	*full_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	path_components = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_components[i] != NULL)
	{
		//printf("hi we are in the loop\n");
		current_path = ft_strjoin(path_components[i], "/");
	//	printf("current path:");
	//	print_path(current_path);
		full_path = ft_strjoin(current_path, cmd);
		// printf("full path:");
		// print_path(full_path);
		free(current_path);
		if (access(full_path, F_OK) == 0)
		{
		//	print_path(full_path);
			return (full_path);
		}
		free (full_path);
		i++;
	}
	i = 0;
	while (path_components[i++])
		free(path_components[i]);
	free(path_components);
	return (cmd);
}

//to execute while iterating cmd

void	env_execute(t_data *shell, char *arg)
{
	char	*path;
	// int		i;

	// i = 0;
	while(arg != NULL)
	{
		path = path_finder(arg, shell->env);
		if(!path)
		{
			// while (shell->arguments[i++])
			// 	free(shell->arguments[i]);
			free(arg);
			perror("Error in Path\n");
			exit(1);
		}
		printf("will executen: %s\n", arg);
		// printf("path in execute:");
		// print_path(path);
		if(execve(path, shell->arguments, shell->env) < 0)  //warum nur moeglich mir shell->arguments und nicht args?
		{
			perror("command couldnt be executed\n");
			// while (shell->arguments[i++])
			// 	free(shell->arguments[i]);
			free(arg);
			exit(1);
		}
		//i++;
	}
	free(arg);
	free(path);
}
