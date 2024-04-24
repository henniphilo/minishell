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
		if (data->bi)
			free(data->bi);
		if (data->arguments)
		{
			i = -1;
			while (data->arguments[++i])
				free(data->arguments[i]);
			free(data->arguments);
		}
		free_tokens(&(data->tokens));
		free(&(data->env_list));
		free_env(data->env);
		free(data);
	}
	return (NULL);
}
