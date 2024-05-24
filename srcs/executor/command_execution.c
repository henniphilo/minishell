/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:17 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/24 12:53:18 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	exec_cmd_helper(char *cmd, char *path)
{
	if (strncmp(cmd, "/", 1) == 0 || strncmp(cmd, "./", 2) == 0)
	{
		perror(cmd);
		return (command_err(NULL, NULL, 127, path));
	}
	else
		return (command_err(cmd, COMMAND_ERR, 127, path));
}

int	execute_command(t_data *shell, t_command *toex)
{
	char		*path;
	struct stat	statbuf;

	path = path_finder(toex->cmd, shell, 0);
	if (!path)
		return (command_err(toex->cmd, COMMAND_ERR, 127, NULL));
	if (stat(path, &statbuf))
		return (exec_cmd_helper(toex->cmd, path));
	if ((strncmp(toex->cmd, "/", 1) == 0 || strncmp(toex->cmd, "./", 2) == 0)
		&& S_ISDIR(statbuf.st_mode))
		return (command_err(toex->cmd, DIR_ERR, 126, path));
	if (strncmp(toex->cmd, "./", 2) == 0)
	{
		if (access(path, X_OK) != 0)
		{
			if (errno == EACCES)
				return (command_err(toex->cmd, PER_ERR, 126, path));
		}
	}
	if (execve(path, toex->argv, shell->env) < 0)
		return (command_err(toex->cmd, COMMAND_ERR, 127, path));
	free(path);
	return (0);
}

void	execution(t_data *shell, t_command *toex)
{
	int	e_code;

	e_code = 0;
	redirect_pipes(toex);
	if (which_builtin_child(shell, toex) != 0)
	{
		e_code = execute_command(shell, toex);
		if (e_code != 0)
			exit(e_code);
	}
	exit(EXIT_SUCCESS);
}
