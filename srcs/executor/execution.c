/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:23:12 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:03:14 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	pipeline_exe(t_data *shell)
{
	t_command	*toex;
	int			i;

	i = 0;
	toex = shell->toex;
	init_pipeline(shell);
	while (toex)
	{
		if (valid_fd_in_out_check(shell, toex) == 1)
		{
			toex = toex->next;
			i++;
			continue ;
		}
		if (!toex->cmd)
		{
			toex = toex->next;
			i++;
			continue ;
		}
		if (builtin_check(toex->cmd) == 1 && !toex->next)
		{
			if (which_builtin_parent(shell, toex->cmd, shell->toex->argv) != 0)
			{
				free_pipes(shell);
				free(shell->pids);
				shell->pids = NULL;
				return (1);
			}
		}
		else
		{
			if (exe_env(shell, shell->pids, i, toex) != 0)
			{
				perror("exe error\n");
				g_estatus = 1;
				return (1);
			}
		}
		toex = toex->next;
		i++;
	}
	wait_for_children(shell);
	free_pipes(shell);
	free (shell->pids);
	shell->pids = NULL;
	return (0);
}

void	env_execute(t_data *shell, char *toex)
{
	char	*path;

	while (toex != NULL)
	{
		path = path_finder(toex, shell);
		if (!path)
		{
			free(toex);
			perror("Error in Path\n");
			exit(1);
		}
		if (execve(path, shell->toex->argv, shell->env) < 0)
		{
			perror("command couldnt be executed\n");
			free(toex);
			exit(1);
		}
	}
	free(toex);
	free(path);
}
