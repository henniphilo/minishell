#include "../../incl/minishell.h"

/*calculates the size of a 2D-array*/
static int	count_ptrs(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

/*stores the variables form envp in data->env*/
void	*init_env(t_data *data, char **envp)
{
	int	i;

	data->env = ft_calloc((count_ptrs(envp) + 1), sizeof(char *));
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
