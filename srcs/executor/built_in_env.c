#include "../../incl/minishell.h"


char	*find_in_env(char *to_find)
{
	char	*value;

	value = getenv(to_find);
	if(!value)
	{
		perror("env value not found\n");
	}
	return (value);
}
//noch beachten dass es unset USER="Henrike" ist also nicht mit weiteren toex[..]

void		bi_unset(t_data *shell)
{
	t_environ	*prev;
	t_environ	*begin;
	t_environ	*remove;
	t_environ	*head;

	begin = shell->env_list;
	head = begin;
	prev = NULL;
	if (shell->toex->args[0] != NULL)
	{
		while(head != NULL)
		{
			if(ft_strncmp(head->name, shell->toex->args[0], 50) == 0)
			{
				if(shell->toex->args[1] == NULL)
				{
					remove = head;
		//			printf(">this to remove: %s=%s < \n", remove->name, remove->value);
					if (prev)
						prev->next = head->next;
					else
						begin = head->next;
		//			printf(">this is tmp: %s=%s < \n", head->name, head->value);
					delone_env_list(remove);
					break ;
				}
				else
				{
					head = replace_value(head, shell->toex->args[1]);
					break ;
				}
			}
			prev = head;
			head = head->next;
		}
	}
//	print_env(begin);
}

t_environ	*replace_value(t_environ *list_ptr, char *replace)
{
	char		*new_value;

	printf("jetzt wird gleich was replacet\n");
	new_value = ft_strdup(replace);
	free(list_ptr->value);
	list_ptr->value = new_value;
	return(list_ptr);
}

/*
static t_environ *sort_env(t_environ *head, t_environ *new_node)
{
    t_environ *current;

    if (head == NULL || ft_strcmp(head->name, new_node->name) > 0)
	{
        new_node->next = head;
        return (new_node);
    }
	else
	{
        current = head;
        while (current->next != NULL && ft_strcmp(current->next->name, new_node->name) <= 0)
		{
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
        return (head);
    }
}

t_environ *sort_export_list(t_environ *head)
{
    t_environ *sorted_head = NULL;
    t_environ *next;

    while (head != NULL)
	{
        sorted_head = sort_env(sorted_head, head);
		head = head->next;
    }
    return (sorted_head);
} */

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
	t_environ	*ptr1;
	t_environ	*lptr;
	int			swapped;

	head = shell->export_list;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				swap(ptr1, ptr1->next);
					swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

static void	only_export(t_data *shell)
{
	// t_environ	*sorted_lst;

	// printf("ist jetzt in only export\n");
	// sorted_lst = sort_export_list(shell->export_list);
	// if(!(sorted_lst))
	// {
	// 	printf("error not sorted list ptr \n");
	// 	return;
	// }
	// else
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
}

void	bi_export(t_data *shell)
{
	init_export_list(shell);
	if(shell->toex->args != NULL)
		export_env(shell);
	else
		//print_export_list(shell);
		only_export(shell);
}
