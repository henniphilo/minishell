/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:23:29 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:13:50 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	builtin_check(char *arg)
{
	int	n;

	n = 7;
	if ((ft_strncmp((const char *)arg, "cd", n) == 0)
		|| (ft_strncmp((const char *)arg, "exit", n) == 0)
		|| (ft_strncmp((const char *)arg, "unset", n) == 0)
		|| (ft_strncmp((const char *)arg, "pwd", n) == 0)
		|| (ft_strncmp((const char *)arg, "export", n) == 0))
		return (1);
	return (0);
}

int	which_builtin_parent(t_data *shell, char *arg, char **argv)
{
	if (ft_strcmp((const char *)arg, "cd") == 0)
		g_estatus = bi_cd(shell);
	else if (ft_strcmp((const char *)arg, "export") == 0)
		g_estatus = bi_export(shell);
	else if (ft_strcmp((const char *)arg, "pwd") == 0)
		g_estatus = bi_pwd(shell);
	else if (ft_strcmp((const char *)arg, "unset") == 0)
	{
		bi_unset(argv, shell->env_list);
		bi_unset(argv, shell->export_list);
		g_estatus = 0;
	}
	else if (ft_strcmp((const char *)arg, "exit") == 0)
	{
		g_estatus = bi_exit(shell, argv);
		free_data(shell);
		exit(g_estatus);
	}
	else
		g_estatus = 1;
	return (g_estatus);
}


int	bi_exit(t_data *shell, char **argv)
{
	int	i;

	i = 0;
	(void)shell;
	if (argv[1])
	{
		if (argv[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
		if (ft_isnum(argv[1]))
			return (2);
		i = ft_atoi(argv[1]);
		return (i);
	}
	else
		return (g_estatus);
	return (0);
}

int	bi_pwd(t_data *shell)
{
	char		cwd[1024];

	shell->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (!shell->pwd)
		return (1);
	else
	{
		printf("%s\n", shell->pwd);
		free(shell->pwd);
		shell->pwd = NULL;
		return (0);
	}
}
