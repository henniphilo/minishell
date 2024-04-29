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
			// printf("das soll geaendert werden: %s\n", shell->toex[1]);
			// printf("next name is %s\n", head->next->name);
		if(ft_strncmp(head->name, shell->toex[1], len) == 0)
		{
			if(shell->toex[2] == NULL)
			{
				printf("there is no toex[2]\n");
				remove = head;
				printf(">this to remove: %s=%s < ", remove->name, remove->value);
				head = head->next;
				free(remove);
				break ;
			}
			else
			{
				printf("hat value\n");
				head->value = shell->toex[2];
			}
		}
		head = head->next;
	}
	printf("----hi-----");
	print_env(begin);
}
