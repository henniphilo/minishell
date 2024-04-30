#include "../../incl/minishell.h"


char	*find_in_env(char *to_find)
{
	char	*path;

	path = getenv(to_find);
	if(!path)
	{
		perror("path not found\n");
	}
	return (path);
}

void		print_env(t_environ *env_ptr)
{
//	int	i;
//	t_environ	*head;

//	head = shell->env_list;
	// i = 0;
	// while(shell->env[i] != NULL)
	// {
	// 	printf("%s\n",shell->env[i]);
	// 	i++;
	// }
	while(env_ptr != NULL)
	{
		printf("%s=", env_ptr->name);
		printf("%s\n", env_ptr->value);
		env_ptr = env_ptr->next;
	}
}
//noch beachten dass es unset USER="Henrike" ist also nicht mit weiteren toex[..]
void		bi_unset(t_data *shell)
{
	t_environ	*head;
	t_environ	*begin;
	t_environ	*remove;
	int			len;

	head = shell->env_list;
	begin = head;
	len = ft_strlen(shell->toex[1]);
	while(head != NULL)
	{
		if(ft_strncmp(head->name, shell->toex[1], len) == 0)
		{
			if(shell->toex[2] == NULL)
			{
				remove = head;
				printf(">this to remove: %s=%s < ", remove->name, remove->value);
				head = head->next;
				free(remove);
				break ;
			}
			else
				head->value = shell->toex[2];
		}
		head = head->next;
	}
	print_env(begin);
}

void		bi_export(t_data *shell)
{
	t_environ	*new_node;
	char		*name;
	char		*value;

	printf("lets start to be export \n");

	name = ft_strdup(shell->toex[1]);
	printf("name is: %s\n", name);
	value = ft_strdup(shell->toex[2]);
	printf("value is: %s\n", value);
	new_node = new_env_node(name, value);
	if(!new_node)
	{
		perror("no new node durch export\n");
		free(name);
		free(value);
	}
	add_env_back(&shell->env_list, new_node);
	printf("------new node list-----\n");
	print_env(shell->env_list);
}
