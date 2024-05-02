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
	int			len; //len spaeter vlt. wegmachen

	begin = shell->env_list;
	head = begin;
	prev = NULL;
	len = ft_strlen(shell->toex[1]);
	if (shell->toex[1] != NULL)
	{
		while(head != NULL)
		{
			if(ft_strncmp(head->name, shell->toex[1], len + 1) == 0)
			{
				if(shell->toex[2] == NULL)
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
					head = replace_value(head, shell->toex[2]);
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

void		bi_export(t_data *shell)
{
	t_environ	*new_node;
	char		*name;
	char		*value;

	name = ft_strdup(shell->toex[1]);
	value = ft_strdup(shell->toex[2]);
	new_node = new_env_node(name, value);
	if(!new_node)
	{
		perror("no new node durch export\n");
		free(name);
		free(value);
	}
	add_env_back(&shell->env_list, new_node);
}
