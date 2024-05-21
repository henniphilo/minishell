#include "../../incl/minishell.h"

int		execute_command(t_data *shell, t_command *toex)
{
	char		*path;
	struct stat	statbuf;

	path = path_finder(toex->cmd, shell);
	if(!path)
	{
		command_err(toex->cmd);
		return (127);
	}
	if (stat(path, &statbuf))
	{
		if (strncmp(toex->cmd, "/", 1) == 0 || strncmp(toex->cmd, "./", 2) == 0)
			perror(toex->cmd);
		else
			command_err(toex->cmd);
		free(path);
		return (127); // Exit with 126 for directory error
	}
    // Check if the path is a directory
    if ((strncmp(toex->cmd, "/", 1) == 0 || strncmp(toex->cmd, "./", 2) == 0) && S_ISDIR(statbuf.st_mode))
    {

		fprintf(stderr, "%s: Is a directory\n", toex->cmd);
		free(path);
		return (126); // Exit with 126 for directory error
    }
	// Check for execute permissions
    if (strncmp(toex->cmd, "./", 2) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			if (errno == EACCES)
			{
				fprintf(stderr, "%s: Permission denied\n", toex->cmd);
				free(path);
				return (126); // Exit with 126 for permission error
			}
		}
	}
	if (execve(path, toex->argv, shell->env) < 0)
	{
		command_err(toex->cmd);
		free(path);
		return (127);
	}
	free(path);
	return (0);
}

void	execution(t_data *shell, t_command *toex)
{
	int	e_code;

	e_code = 0;
	if (which_builtin_child(shell, toex) != 0)
	{
		e_code = execute_command(shell, toex);
		if (e_code != 0)
			exit(e_code); //sollten wir nicht statt exit returnen?
	}
	exit(EXIT_SUCCESS); //sollten wir nicht statt exit returnen?
}
