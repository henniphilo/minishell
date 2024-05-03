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
			printf("%s", head->value);
			break ;
		}
		head = head->next;
	}
	free(name);
}

static int	set_flag(t_data *shell)
{
	int		j;
	int		flag;

	flag = 0;
	if(shell->toex->args[0][0] == '-' && shell->toex->args[0][1] == 'n')
	{
		j = 1;
		while(shell->toex->args[0][j] != '\0')
		{
			if(shell->toex->args[0][j] == 'n')
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
	return(flag);
}
// bei echo tilde home noch einfuegen
void		bi_echo(t_data *shell)
{
	int		i;
	int		flag;

	i = 1;
	flag = set_flag(shell);
	printf("flag is %d\n", flag);
	while(shell->toex->args[i] != NULL)
	{
		if(flag == 1)
			i++;
		if(shell->toex->args[i][0]== '$')
		{
			echo_env(shell, shell->toex->args[i]);
			break ;
		}
		else
			printf("%s ", shell->toex->args[i]);
		i++;
	}
	if(flag == 0)
		printf("\n");
}

// macht bei -n $HOME noch new line

