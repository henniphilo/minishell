#include "../../incl/minishell.h"

int		execute_command(t_data *shell, t_command *toex)
{
	char	*path;

	path = path_finder(toex->cmd, shell);
	if(!path)
	{
		free(path);
		panic("error in path", shell, 1);
	}
	if (execve(path, toex->argv, shell->env) < 0)
	{
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
	if (which_builtin_child(shell, toex->cmd) != 0)
	{
		e_code = execute_command(shell, toex);
		if (e_code != 0)
		{
			command_err(toex->cmd);
			exit(e_code);
		}
	}
	exit(EXIT_SUCCESS);
}
