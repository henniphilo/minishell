/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:05:26 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/24 11:06:02 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*frees the stored environmental variables*/
void	free_env(char **env)
{
	int	i;

	if (env)
	{
		i = -1;
		while (env[++i])
			free(env[i]);
		free(env);
	}
}

/*function to free buffer and parsing + lexing
structures before reentering the prompt loop*/
void	clear_data(t_data *shell)
{
	if (shell->buf)
	{
		free(shell->buf);
		shell->buf = NULL;
	}
	unlink("tmp_file");
	free_tokens(&(shell->tokens));
	free_commands(&(shell->toex));
}

static void	free_location(t_data *shell)
{
	if (shell->home)
		free(shell->home);
	if (shell->pids)
		free(shell->pids);
	if (shell->pwd)
	{
		free(shell->pwd);
		shell->pwd = NULL;
	}
}

/*frees every element of the t_data *shell struct*/
void	*free_data(t_data *shell)
{
	int	i;

	i = 0;
	if (shell)
	{
		clear_data(shell);
		free_location(shell);
		free_env_list(&(shell->env_list));
		free_env_list(&(shell->export_list));
		free_env(shell->env);
		if (shell->fd)
		{
			while (shell->fd[i])
			{
				free(shell->fd[i]);
				i++;
			}
			free(shell->fd);
		}
		free(shell);
	}
	return (NULL);
}
