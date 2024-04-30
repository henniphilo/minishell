#include "../../incl/minishell.h"

int	which_builtin_child(t_data *shell, char *arg)
{
	int	n;

	n = 7;
	shell->bi_check = 1;
	if(ft_strncmp((const char *)arg, "env", n) == 0)
	{
		print_env(shell->env_list);
		return(0);
	}
	if(ft_strncmp((const char *)arg, "echo", n) == 0)
	{
		bi_echo(shell);
		return(0);
	}
	return(1);
}

void		print_env(t_environ *env_ptr)
{
	while(env_ptr != NULL)
	{
		printf("%s=", env_ptr->name);
		printf("%s\n", env_ptr->value);
		env_ptr = env_ptr->next;
	}
}

void		echo_env(t_data *shell, char *str)
{
	int			n;
	int			j;
	char		*name;
	t_environ	*head;

	head = shell->env_list;
	j = 1;
	n = ft_strlen(str);
	name = (char*)malloc(sizeof(char) * (n - 1));
	while(str[j] != '\0')
	{
		name[j - 1] = str[j];
		j++;
	}
	printf("name is: %s\n", name);
	while(head != NULL)
	{
		if(ft_strncmp(name, head->name, n - 1) == 0)
		{
			printf("%s\n", head->value);
			return ;
		}
		head = head->next;
	}
	free(name);
}

void		bi_echo(t_data *shell)
{
	int			i;
	int			j;
	bool		flag;

	i = 1;
	if(shell->toex[1][0] == '-' && shell->toex[1][1] == 'n')
	{
		j = 2;
		while(shell->toex[1][j] != '\0')
		{
			if(shell->toex[1][j] == 'n') 
			{
				flag = 1;
				j++;
			}
			else
			{
				flag = 0;
				break ;
			}
		}
	}
	while(shell->toex[i] != NULL)
	{
		//hier stimmt noch was nicht in logik von i, wenn flag 1 -n ueberspringen
		//hier muss es ordfentlich geparst werden von petra und dann kann variable aus der list geprintet werden
		if(flag == 1)
			i++;
		if(shell->toex[i][0]== '$')
		{
			echo_env(shell, shell->toex[i]);
			return ;
		}
		else
			printf("%s ", shell->toex[i]);
		i++;
	}
	if(flag == 0)
		printf("\n");
}
