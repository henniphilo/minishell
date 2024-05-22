/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:23:48 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/22 15:26:15 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	which_builtin_child(t_data *shell, t_command *toex)
{
	if (ft_strcmp(toex->cmd, "env") == 0)
	{
		g_estatus = print_env(shell->env_list);
		return (0);
	}
	else if (ft_strcmp(toex->cmd, "echo") == 0)
	{
		g_estatus = bi_echo(toex);
		return (0);
	}
	else
		g_estatus = 1;
	return (g_estatus);
}

int	print_env(t_environ *env_ptr)
{
	if (!env_ptr)
		return (1);
	while (env_ptr != NULL)
	{
		printf("%s=", env_ptr->name);
		printf("%s\n", env_ptr->value);
		env_ptr = env_ptr->next;
	}
	return (0);
}

void	echo_env(t_data *shell, char *str)
{
	int			n;
	int			j;
	char		*name;
	t_environ	*head;

	head = shell->env_list;
	j = 1;
	n = ft_strlen(str);
	name = (char *)malloc(sizeof(char) * (n - 1));
	while (str[j] != '\0')
	{
		name[j - 1] = str[j];
		j++;
	}
	while (head != NULL)
	{
		if (ft_strncmp(name, head->name, n - 1) == 0)
		{
			printf("%s", head->value);
			break ;
		}
		head = head->next;
	}
	free(name);
}

static int	set_flag(t_command *toex)
{
	int		j;
	int		flag;

	flag = 0;
	if (toex->args[0][0] == '-' && toex->args[0][1] == 'n')
	{
		j = 1;
		while (toex->args[0][j] != '\0')
		{
			if (toex->args[0][j] == 'n')
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
	return (flag);
}

int	bi_echo(t_command *toex)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (toex->args)
	{
		flag = set_flag(toex);
		if (flag == 1)
			i++;
		while (toex->args[i])
		{
			printf("%s", toex->args[i]);
			if (toex->args[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (flag == 0)
		printf("\n");
	return (0);
}
