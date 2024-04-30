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

/*function to free buffer and parsing + lexing structures before reentering the loop*/
void	clear_data(t_data *data)
{
	if (data->buf)
	{
		free(data->buf);
		data->buf = NULL;
	}
	free_tokens(&(data->tokens));
	free_commands(&(data->commands));
}

/*frees every element of the t_data *data struct*/
void	*free_data(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->buf)
			free(data->buf);
		if (data->fd)
			free(data->fd);
		if (data->arguments)
		{
			i = -1;
			while (data->arguments[++i])
				free(data->arguments[i]);
			free(data->arguments);
		}
		free_tokens(&(data->tokens));
		free_commands(&(data->commands));
		free_env_list(&(data->env_list));
		free_env(data->env);
		free(data);
	}
	return (NULL);
}
