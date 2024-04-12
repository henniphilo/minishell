#include "../../incl/minishell.h"


void	*free_data(t_data *data)
{
	int	i;


	if (data)
	{
		if (data->buf)
			free(data->buf);
		if (data->env)
		{
			i = -1;
			while (data->env[++i])
				free(data->env[i]);
			free(data->env);
		}
		free(data);
	}
	return (NULL);
}
