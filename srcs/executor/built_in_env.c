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

void		print_env(t_data *shell)
{
//	int	i;
	t_environ	*head;

	head = shell->env_list;
	// i = 0;
	// while(shell->env[i] != NULL)
	// {
	// 	printf("%s\n",shell->env[i]);
	// 	i++;
	// }

	while(head != NULL)
	{
		printf("%s=", head->name);
		printf("%s\n", head->value);
		head = head->next;
	}
}
