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

/* t_environ	*init_env_list(char **envp)
{
	t_environ	*list;
	int			i;
	char		*value;
	char		*name;

	if (envp)
	{
		i = -1;
		while (envp[++i])
		{
			name = ft_substr(envp[i], 0, ft_strchr(envp[i], "=") - envp[i]);
			value = ft_substr(envp[i], (ft_strchr(envp[i], "=") - envp[i]) + 1, ft_strlen((const char *)envp[i]));
			new_env_node();
			add_env_back();
		}
	}
} */

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
