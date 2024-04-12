#include "../../incl/minishell.h"

void	*init_data(t_data *data, char **envp)
{
	int	i;

	data->env = ft_calloc((ft_strlen(envp) + 1), sizeof(char *));
	if (!data->env)
		panic(ALLOC_ERR, data);
	i = -1;
	while (envp[++i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			panic(ALLOC_ERR, data);
	}
	return (NULL);
}
