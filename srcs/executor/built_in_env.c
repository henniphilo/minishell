#include "../../incl/minishell.h"

char	*find_in_env(char *to_find)
{
	char	*value;

	value = getenv(to_find);
	if(!value)
		return (NULL);
	return (value);
}

int		bi_unset(char **argv, t_environ *list)
{
	t_environ	*prev;
	t_environ	*head;
	int			i;

	if (argv[1] == NULL)
		return (0);
	prev = NULL;
	i = 1;
	while (argv[i] != NULL)
	{
		head = list;
		while(head != NULL)
		{
			if(ft_strcmp(head->name, argv[i]) == 0)
			{
				remove_node(head, head, &list, prev);
				break;
			}
			prev = head;
			head = head->next;
		}
		i++;
	}
	return (0);
}

void	remove_node(t_environ *remove, t_environ *head, t_environ **list, t_environ *prev)
{
	if (prev)
		prev->next = head->next;
	else
		*list = head->next;
	delone_env_list(remove);
}

t_environ	*replace_value(t_environ *list_ptr, char *replace)
{
	if (list_ptr->value)
		free(list_ptr->value);
	list_ptr->value = replace;
	return(list_ptr);
}
