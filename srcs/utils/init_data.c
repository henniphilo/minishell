#include "../../incl/minishell.h"

void	*init_data(t_data *data)
{
	int	i;

	data->env = ft_calloc((ft_strlen(environ) + 1), sizeof(char *));
	if (!data->env)
		panic(ALLOC_ERR, data);
	i = -1;
	while (environ[++i])
	{
		data->env[i] = ft_strdup(environ[i]);
		if (!data->env[i])
			panic(ALLOC_ERR, data);
	}
	return (NULL);
}
