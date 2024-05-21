#include "../../incl/minishell.h"

int		execute_command(t_data *shell, t_command *toex)
{
	char		*path;
	struct stat	statbuf;

	path = path_finder(toex->cmd, shell);
	if(!path)
	{
		command_err(toex->cmd);
		free(path);
		return (127);
		//panic("error in path", shell, 1);
	}
	if (stat(path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		direc_err(toex->cmd);
		free(path);
		return (126);
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
			exit(e_code);
	}
	exit(EXIT_SUCCESS);
}
