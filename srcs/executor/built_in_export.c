/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:24:31 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/23 18:11:25 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_environ	*list_duplicate(t_environ *lst_ptr)
{
	t_environ	*new_lst;
	t_environ	*node;
	char		*value;
	char		*name;

	new_lst = NULL;
	while (lst_ptr != NULL)
	{
		name = ft_strdup(lst_ptr->name);
		value = ft_strdup(lst_ptr->value);
		if (!name || !value)
		{
			free_strs(name, value);
			return (NULL);
		}
		node = new_env_node(name, value);
		if (!node)
		{
			free_strs(name, value);
			return (NULL);
		}
		add_env_back(&new_lst, node);
		lst_ptr = lst_ptr->next;
	}
	return (new_lst);
}

// wird gebraucht um export variablen zu storen
void	init_export_list(t_data *shell)
{
	shell->export_list = list_duplicate(shell->env_list);
	if (!shell->export_list)
		panic(ALLOC_ERR, shell, 1);
}

static void	swap(t_environ *a, t_environ *b)
{
	char	*temp_name;
	char	*temp_value ;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_export_list(t_data *shell)
{
	t_environ	*head;
	t_environ	*current;
	t_environ	*last_sort;
	int			swapped;

	head = shell->export_list;
	last_sort = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current->next != last_sort)
		{
			if (ft_strcmp(current->name, current->next->name) > 0)
			{
				swap(current, current->next);
					swapped = 1;
			}
			current = current->next;
		}
		last_sort = current;
	}
}

void	print_export_list(t_data *shell)
{
	t_environ	*export_lst;

	export_lst = shell->export_list;
	while(export_lst != NULL)
	{
		printf("export_list....");
		printf("%s=", export_lst->name);
		printf("%s\n", export_lst->value);
		export_lst = export_lst->next;
	}
}

static void	only_export(t_data *shell)
{
	sort_export_list(shell);
	print_export_list(shell);
}

int		export_env(t_data *shell, char *arg)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_substr(arg, ft_strchr(arg, '=')- arg + 1, ft_strlen(arg));
	if (!name || !value)
		return (free_strs(name, value));
	head = find_name_in_envlist(shell, name);
	if (!head)
	{
		new_node = new_env_node(name, value);
		if (!new_node)
		{
			error_int(ALLOC_ERR);
			return (free_strs(name, value));
		}
		add_env_back(&shell->env_list, new_node);
	}
	else
	{
		head = replace_value(head, value);
		free(name);
	}
	return (0);
}

int		export_export(t_environ *export_list, char *arg)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_substr(arg, ft_strchr(arg, '=')- arg + 1, ft_strlen(arg));
	if (!name || !value)
		return (free_strs(name, value));
	head = find_name_in_exportlist(export_list, name);
	if (!head)
	{
		new_node = new_env_node(name, value);
		if (!new_node)
			return (free_strs(name, value));
		add_env_back(&export_list, new_node);
	}
	else
	{
		head = replace_value(head, value);
		free(name);
	}
	return (0);
}

int		to_export_list(t_data *shell, char *arg)
{
	t_environ	*new_node;
	char		*name;
	char		*value;

	name = ft_strdup(arg);
	value = ft_strdup("");
	if (!name || !value)
		return (free_strs(name, value));
	new_node = new_env_node(name, value);
	if (!new_node)
	{
		ft_putstr_fd("no new node in export list\n", 2);
		return (free_strs(name, value));
	}
	add_env_back(&shell->export_list, new_node);
	return (0);
}

int		bi_export(t_data *shell)
{
	int		i;

	i = -1;
	if (shell->toex->args == NULL)
		only_export(shell);
	else
	{
		while (shell->toex->args[++i] != NULL && !check_doubles(shell->toex->args, i))
		{
			if (identifier_check(shell->toex->args[i]) == 1)
				return (ident_error_int(shell->toex->args[i]));
			if (!(ft_strchr(shell->toex->args[i], '=')))
			{
				if (to_export_list(shell, shell->toex->args[i]))
					return (1);
			}
			else
			{
				if (export_env(shell, shell->toex->args[i])
					|| export_export(shell->export_list, shell->toex->args[i]))
					return (1);
			}
		}
	}
	return (0);
}

int		identifier_check(char *arg)
{
	int		i;

	i = 0;
	if (arg[0] == '=' || (arg[i] >= 48 && arg[i] <= 57))
		return (1);
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!((arg[i] >= 48 && arg[i] <= 57) || (arg[i] >= 65 && arg[i] <= 90)
				|| (arg[i] >= 97 && arg[i] <= 122)))
			return (1);
		i++;
	}
	return (0);
}
