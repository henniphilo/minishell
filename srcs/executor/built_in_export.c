/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:24:31 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/24 11:04:48 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	only_export(t_data *shell)
{
	sort_export_list(shell);
	print_export_list(shell);
}

int	export_env(t_data *shell, char *arg)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg));
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

int	export_export(t_environ *export_list, char *arg)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;

	name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg));
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

int	to_export_list(t_data *shell, char *arg)
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

int	bi_export(t_data *shell)
{
	int		i;

	i = -1;
	if (shell->toex->args == NULL)
		only_export(shell);
	else
	{
		while (shell->toex->args[++i] != NULL
			&& !check_doubles(shell->toex->args, i))
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
