/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:23:12 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/24 15:58:29 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	free_pipes_return(t_data *shell, int ret)
{
	free_pipes(shell);
	free (shell->pids);
	shell->pids = NULL;
	return (ret);
}

int	pipeline_exe(t_data *shell, t_command *toex)
{
	int	i;

	i = -1;
	while (toex)
	{
		i++;
		if (valid_fd_in_out_check(shell, toex) == 1 || !toex->cmd)
		{
			toex = toex->next;
			continue ;
		}
		if (builtin_check(toex->cmd) == 1 && !toex->next)
		{
			if (which_builtin_parent(shell, toex->cmd, shell->toex->argv) != 0)
				return (free_pipes_return(shell, 1));
		}
		else if (exe_env(shell, shell->pids, i, toex) != 0)
		{
			g_estatus = 1;
			return (error_int(EXEC_ERR));
		}
		toex = toex->next;
	}
	wait_for_children(shell);
	return (free_pipes_return(shell, 0));
}

void	env_execute(t_data *shell, char *toex)
{
	char	*path;

	while (toex != NULL)
	{
		path = path_finder(toex, shell, 0);
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
