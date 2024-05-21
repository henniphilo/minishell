#include "../../incl/minishell.h"

int		execute_command(t_data *shell, t_command *toex)
{
	char		*path;
	struct stat	statbuf;

	path = path_finder(toex->cmd, shell);
	if(!path)
		return (command_err(toex->cmd, COMMAND_ERR, 127, NULL));
	if (stat(path, &statbuf))
	{
		if (strncmp(toex->cmd, "/", 1) == 0 || strncmp(toex->cmd, "./", 2) == 0)
		{
			perror(toex->cmd);
			return (command_err(NULL, NULL, 127, path));
		}
		else
			return (command_err(toex->cmd, COMMAND_ERR, 127, path));
	}
	if ((strncmp(toex->cmd, "/", 1) == 0 || strncmp(toex->cmd, "./", 2) == 0) && S_ISDIR(statbuf.st_mode))
		return (command_err(toex->cmd, DIR_ERR, 126, path));
	if (strncmp(toex->cmd, "./", 2) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			if (errno == EACCES)
				return (command_err(toex->cmd, PER_ERR, 126, path));
		}
	}
	if (execve(path, toex->argv, shell->env) < 0)
		return (command_err(toex->cmd, COMMAND_ERR, 127, path));
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
