#include "../../incl/minishell.h"

int		execute_command(t_data *shell, t_command *toex)
{
	char	*path;

	path = path_finder(toex->cmd, shell);
	if(!path)
	{
		perror("Error in Path\n");
		exit(1);
	}
//	printf("executet: %s\n", toex->cmd);
	if(execve(path, toex->argv, shell->env) < 0)
		return (127);
	free(path);
	return (0);
}

void	execution(t_data *shell, t_command *toex)
{
	if (which_builtin_child(shell, toex->cmd) != 0)
	{
		if (execute_command(shell, toex) != 0)
		{
			command_err(toex->cmd);
			exit(127);
		}
	}
	exit(EXIT_SUCCESS);
}
