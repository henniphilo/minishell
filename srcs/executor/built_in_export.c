#include "../../incl/minishell.h"

t_environ	*list_duplicate(t_environ *lst_ptr)
{
	t_environ	*new_lst;
	t_environ	*node;
	char		*value;
	char		*name;

	new_lst = NULL;
	while(lst_ptr != NULL)
	{
		name = ft_strdup(lst_ptr->name);
		value = ft_strdup(lst_ptr->value);
		node = new_env_node(name, value);
		if (!node)
		{
			free(name);
			free(value);
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

//soll bei env_list und export list hinzufuegen
int		export_env(t_data *shell, char *arg)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;
	char		*limit;

	limit = ft_strchr(arg, '=');
	name = ft_substr(arg, 0, limit - arg);
	value = ft_substr(arg, limit - arg + 1, ft_strlen(arg));
	head = find_name_in_envlist(shell, name);
	if (!head)
	{
		new_node = new_env_node(name, value);
		if (!new_node)
		{
			perror("no new node durch export\n");
			free(name);
			free(value);
			return (1);
		}
		add_env_back(&shell->env_list, new_node);
		//add_env_back(&shell->export_list, new_node); //?
	}
	else
	{
		head = replace_value(head, value); //muss auch im export list replacet werden
		free(name);
		free(value);
	}
	// printf("-----das ist env---\n");
	// print_env(shell->env_list);
	// free_env_list(&shell->export_list);
	// init_export_list(shell);
	// printf("-----das ist export---\n");
	// print_export_list(shell);
	return (0);
}

// hier noch loop fuer mehrere argumente mit space getrennt ist jeweils ein neuer node im export list
// fuegt nur bei export list hinzu
int		to_export_list(t_data *shell, char *arg)
{
	t_environ	*new_node;
	char		*name;
	char		*value;

	name = ft_strdup(arg);
	value = ft_strdup("");
	new_node = new_env_node(name, value);
	if (!name || name[0] < 65 || !value || !new_node)
	{
		ft_putstr_fd("no new node in export list\n", 2);
		if (name)
			free(name);
		if (value)
			free(value);
		if (new_node)
			free(new_node);
		return (1);
	}
	add_env_back(&shell->export_list, new_node);
	return (0);
}

int		bi_export(t_data *shell)
{
	int		i;
	int		result;

	i = 0;
	if (shell->toex->args == NULL)
	{
		only_export(shell);
		return (0);
	}
	else
	{
		while (shell->toex->args[i] != NULL)
		{
			if (identifier_check(shell->toex->args[i]) == 1) // checken nur bei erstem vor =
				return (ident_error_int(shell->toex->args[i]));
			if (!(ft_strchr(shell->toex->args[i], '=')))
				result = to_export_list(shell, shell->toex->args[i]);
			else
				result = export_env(shell, shell->toex->args[i]);
			i++;
		}
	}
	//printf("result ist gerade %d\n", result);
	return (result);
}

int		identifier_check(char *arg) //darf nur anschauen was vor = ist also A-=hallo darf nicht moeglich sein aber dafuer A=hallo-
{
	int		i;

	i = 0;
	if (arg[0] == '=')
		return (1);
	while(arg[i] != '\0' && arg[i] != '=')
	{
		if (!((arg[i] >= 48 && arg[i] <= 57) || (arg[i] >= 65 && arg[i] <= 90)
			|| (arg[i] >= 97 && arg[i] <= 122)))
			return (1);
		i++;
	}
	return (0);
}
