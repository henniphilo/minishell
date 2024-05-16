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

//wie umgehen mit istgleich ??? -> petra schreibt funktion
void		export_env(t_data *shell)
{
	t_environ	*new_node;
	t_environ	*head;
	char		*name;
	char		*value;

	name = ft_strdup(shell->toex->args[0]);
	value = ft_strdup(shell->toex->args[1]);
	head = find_name_in_envlist(shell, name);
	if (!head)
	{
		new_node = new_env_node(name, value);
		if (!new_node)
		{
			perror("no new node durch export\n");
			free(name);
			free(value);
		}
		add_env_back(&shell->env_list, new_node);
	}
	else
	{
		head = replace_value(head, value);
		free(name);
		free(value);
	}
	print_env(shell->env_list);
}

void	to_export_list(t_data *shell)
{
	t_environ	*new_node;
	char		*name;
	char		*value;

	name = ft_strdup(shell->toex->args[0]);
	value = " ";
	new_node = new_env_node(name, value);
	printf("ist in to export list drin\n");
	if (!new_node)
	{
		perror("no new node in export list\n");
		free(name);
//		free(value);
	}
	add_env_back(&shell->export_list, new_node);
}

void	bi_export(t_data *shell)
{
	if(shell->toex->args != NULL)
	{
		if(shell->toex->args[1] == NULL)
			to_export_list(shell);
		else
			export_env(shell);
	}
	else
		only_export(shell);
}
