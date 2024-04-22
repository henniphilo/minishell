#include "../../incl/minishell.h"

static int	count_ptrs(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	*init_data(t_data *data, char **envp)
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
	data->tokens = ft_calloc(1, sizeof(t_lexer));
	if (!data->tokens)
		panic(ALLOC_ERR, data);
	return (NULL);
}
