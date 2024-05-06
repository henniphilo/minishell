
#include "../../incl/minishell.h"

void	print_path(char *path)
{
//	printf("hi in print_path\n");
	if(path != NULL)
		printf("path: %s\n", path);
}


char	*path_finder(char *cmd, t_data *shell)
{
	int		i;
	char	**path_components;
	char	*current_path;
	char	*full_path;

	i = 0;
	while (ft_strnstr(shell->env[i], "PATH=", 5) == 0)
		i++;
	path_components = ft_split(shell->env[i] + 5, ':');
	i = 0;
	while (path_components[i] != NULL)
	{
		current_path = ft_strjoin(path_components[i], "/");
		full_path = ft_strjoin(current_path, cmd);
		free(current_path);
		if (access(full_path, F_OK) == 0)
		{
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

void	env_execute(t_data *shell, char *toex)
{
	char	*path;

	while(toex != NULL)
	{
		path = path_finder(toex, shell);
		if(!path)
		{
			free(toex);
			perror("Error in Path\n");
			exit(1);
		}
		printf("will executen: %s\n", toex);
		// printf("path in execute:");
		// print_path(path);
		if(execve(path, shell->toex->argv, shell->env) < 0)  //warum nur moeglich mir shell->arguments und nicht args?
		{
			perror("command couldnt be executed\n");
			free(toex);
			exit(1);
		}
	}
	free(toex);
	free(path);
}
