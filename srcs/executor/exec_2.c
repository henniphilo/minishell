
#include "../../incl/minishell.h"

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
	while (path_components[i])
	{
		current_path = ft_strjoin(path_components[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		free(current_path);
		if (access(current_path, F_OK) == 0)
			return (full_path);
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

void	execute(t_data *shell, char **envp)
{
	char	*path;
	int		i;

	//shell->env = envp;
	i = 0;
	path = path_finder(shell->arguments[i], envp);
	if(!path)
	{
		while (shell->arguments[i++])
			free(shell->arguments[i]);
		free(shell->arguments);
		perror("Error in Path\n");
		exit(1);
	}
	if(execve(path, shell->arguments, envp) < 0)
	{
		perror("command couldnt be executed\n");
		while (shell->arguments[i++])
			free(shell->arguments[i]);
		free(shell->arguments);
		exit(1);
	}
	free(shell->arguments);
	free(path);
}



