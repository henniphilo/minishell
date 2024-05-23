/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:14 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 17:50:08 by hwiemann         ###   ########.fr       */
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

void	print_export_list(t_data *shell)
{
	t_environ	*export_lst;

	export_lst = shell->export_list;
	while (export_lst != NULL)
	{
		printf("export_list....");
		printf("%s=", export_lst->name);
		printf("%s\n", export_lst->value);
		export_lst = export_lst->next;
	}
}

int	identifier_check(char *arg)
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
