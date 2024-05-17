
#include "../../incl/minishell.h"

void	print_path(char *path)
{
	if(path != NULL)
		printf("path: %s\n", path);
}

int		var_check(t_data *shell, char *to_check)
{
	t_environ	*check;

	check = find_name_in_envlist(shell, to_check);
	if (!check)
		return (1);
	return (0);
}
char	**get_path_components(t_data *shell)
{
	int		i;
	char	**path_components;

	i = 0;
	path_components = NULL;
	if (var_check(shell, "PATH") == 0)
	{
		while (shell->env[i] && ft_strnstr(shell->env[i], "PATH=", 5) == 0)
			i++;
		if (shell->env[i])
			path_components = ft_split(shell->env[i] + 5, ':');
	}
	return (path_components);
}

char	*path_finder(char *cmd, t_data *shell)
{
	char	**path_components;
	char	*current_path;
	char	*full_path;
	int		i;

	i = 0;
	path_components = get_path_components(shell);
	if(path_components == NULL)
		return (NULL);

	while (path_components[i] != NULL)
	{
		current_path = ft_strjoin(path_components[i], "/");
		full_path = ft_strjoin(current_path, cmd);
		free(current_path);
		if (access(full_path, F_OK) == 0)
		{
			free_split(path_components);
			return (full_path);
		}
		free (full_path);
		i++;
	}
	free_split(path_components);
	return (cmd);
}

void	free_split(char **split_components)
{
	int		i;

	i = 0;
	while(split_components[i])
	{
		free(split_components[i]);
		i++;
	}
	free(split_components);
}

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
		if(execve(path, shell->toex->argv, shell->env) < 0)
		{
			perror("command couldnt be executed\n");
			free(toex);
			exit(1);
		}
	}
	free(toex);
	free(path);
}
