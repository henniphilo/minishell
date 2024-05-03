#include "../../incl/minishell.h"

/*frees the stored environmental variables*/
void	free_env(char **env)
{
	int	i;

	if (env)
	{
		i = -1;
		while (env[++i])
			free(env[i]);
		free(env);
	}
}

/*function to free buffer and parsing + lexing structures before reentering the prompt loop*/
void	clear_data(t_data *shell)
{
	if (shell->buf)
	{
		free(shell->buf);
		shell->buf = NULL;
	}
	free_tokens(&(shell->tokens));
	free_commands(&(shell->toex));
}

/*frees every element of the t_data *shell struct*/
void	*free_data(t_data *shell)
{
	if (shell)
	{
		if (shell->buf)
			free(shell->buf);
		if (shell->fd)
			free(shell->fd);
		free_tokens(&(shell->tokens));
		free_commands(&(shell->toex));
		free_env_list(&(shell->env_list));
		free_env(shell->env);
		free(shell);
	}
	return (NULL);
}
