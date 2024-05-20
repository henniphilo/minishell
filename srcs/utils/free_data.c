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
	unlink("tmp_file");
	if (g_estatus)
	{
		shell->exit_status = g_estatus; ///???
		g_estatus = 0;
	}
	else
		shell->exit_status = 0;
	free_tokens(&(shell->tokens));
	free_commands(&(shell->toex));
}

/*frees every element of the t_data *shell struct*/
void	*free_data(t_data *shell)
{
	if (shell)
	{
		clear_data(shell);
		if(shell->pids != NULL)
			free(shell->pids);
		free_env_list(&(shell->env_list));
		free_env_list(&(shell->export_list));
		free_env(shell->env);
		free(shell);
	}
	return (NULL);
}
