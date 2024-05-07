#include "../../incl/minishell.h"

//nur export:
//liste duplizieren, wenn nur export henni ohne value soll auf diese liste
//dann sortieren
// dann ausdrucken wenn nur export

//drickt jetzt die neue liste - aber an falscher stelle

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
		panic(ALLOC_ERR, shell);
}


void	print_export_list(t_data *shell)
{
	printf("muss noch sortiert werden, hier die neue liste: \n");
	print_env(shell->export_list);
}

