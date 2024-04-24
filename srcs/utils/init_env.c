#include "../../incl/minishell.h"

t_environ	*new_env_node(char *name, char *value)
{
	t_environ	*node;

	node = malloc(sizeof(t_environ));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_environ	*env_list_last(t_environ *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void	add_env_back(t_environ **list, t_environ *node)
{
	t_environ	*tmp;

	if (list)
	{
		tmp = env_list_last(*list);
		if (tmp)
			tmp->next = node;
		else
			*list = node;
	}

}

t_environ	*init_env_list(char **envp)
{
	t_environ	*list;
	t_environ	*node;
	char		*value;
	char		*name;

	list = NULL;
	if (!envp || !(*envp))
		return (NULL);
	while (*envp)
	{
		name = ft_substr(*envp, 0, ft_strchr(*envp, '=') - *envp);
		value = ft_substr(*envp, (ft_strchr(*envp, '=') - *envp) + 1, ft_strlen((const char *)(*envp)));
		node = new_env_node(name, value);
		if (!node)
		{
			free(name);
			free(value);
			return (NULL);
		}
		add_env_back(&list, node);
		envp++;
	}
	return (list);
}

/*stores the variables form envp in data->env*/
void	*init_env(t_data *data, char **envp)
{
	int	i;

	data->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
	if (!data->env)
		panic(ALLOC_ERR, data);
	i = -1;
	while (envp[++i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			panic(ALLOC_ERR, data);
	}
	data->env_list = init_env_list(envp);
	if (!data->env_list)
		panic(ALLOC_ERR, data);
	return (NULL);
}
