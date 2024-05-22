#include "../../incl/minishell.h"

char	*find_in_env(char *to_find)
{
	char	*value;

	value = getenv(to_find);
	if(!value)
		return (NULL);
	return (value);
}

int		bi_unset(t_data *shell)
{
	t_environ	*prev;
	t_environ	*begin;
	t_environ	*remove;
	t_environ	*head;
	int			i;

	begin = shell->env_list;
	head = begin;
	prev = NULL;
	if (shell->toex->argv[1] == NULL)
		return (0);
	i = 1;
	while (shell->toex->argv[i] != NULL)
	{
		while(head != NULL)
		{
			if(ft_strcmp(head->name, shell->toex->args[0]) == 0)
			{
				remove = head;
				if (prev)
					prev->next = head->next;
				else
					begin = head->next;
				delone_env_list(remove);
				break ;
			}
			prev = head;
			head = head->next;
		}
		i++;
	}
	return (0);
}

t_environ	*replace_value(t_environ *list_ptr, char *replace)
{
	if (list_ptr->value)
		free(list_ptr->value);
	list_ptr->value = replace;
	return(list_ptr);
}
