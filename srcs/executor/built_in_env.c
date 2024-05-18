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

int		bi_unset(t_data *shell)
{
	t_environ	*prev;
	t_environ	*begin;
	t_environ	*remove;
	t_environ	*head;

	begin = shell->env_list;
	head = begin;
	prev = NULL;
	if (shell->toex->argv[1] != NULL)
	{
		while(head != NULL)
		{
			if(ft_strncmp(head->name, shell->toex->args[0], 50) == 0)
			{
				if(shell->toex->args[1] == NULL)
				{
					remove = head;
					if (prev)
						prev->next = head->next;
					else
						begin = head->next;
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
		return (0);
	}
	return (1);
}

t_environ	*replace_value(t_environ *list_ptr, char *replace)
{
	char		*new_value;

	new_value = ft_strdup(replace);
	if (!new_value)
		return (NULL);
	free(list_ptr->value);
	list_ptr->value = new_value;
	return(list_ptr);
}
