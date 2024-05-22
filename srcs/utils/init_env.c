/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:07:34 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/22 10:14:57 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*creates a new env node*/
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

/*searches for the last element of the env list*/
t_environ	*env_list_last(t_environ *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

/*adds an env node to the back of the list*/
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

/*creates a linked list of environment variables; pros: easy to manipulate*/
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
		value = ft_substr(*envp, (ft_strchr(*envp, '=') - *envp) + 1,
				ft_strlen((const char *)(*envp)));
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
void	*init_env(t_data *shell, char **envp)
{
	int	i;

	shell->env = ft_calloc((array_len(envp) + 1), sizeof(char *));
	if (!shell->env)
		panic(ALLOC_ERR, shell, 1);
	i = -1;
	shell->home = ft_strdup(getenv("HOME"));
	if (!shell->home)
		panic(ALLOC_ERR, shell, 1);
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			panic(ALLOC_ERR, shell, 1);
	}
	shell->env_list = init_env_list(envp);
	if (!shell->env_list)
		panic(ALLOC_ERR, shell, 1);
	init_export_list(shell);
	return (NULL);
}
