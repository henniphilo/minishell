/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:27 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:01:59 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	**creating_pipes(t_data *shell)
{
	int		**piped_fd;
	int		i;

	i = 0;
	piped_fd = (int **)ft_calloc(shell->cmd_count, sizeof(int *));
	if (!piped_fd)
	{
		perror("could not create pipe\n");
		return (NULL);
	}
	while (i < shell->cmd_count - 1)
	{
		piped_fd[i] = (int *) ft_calloc(2, sizeof(int));
		if (pipe(piped_fd[i]) == -1)
		{
			perror("pipe error");
			while (i >= 0)
				free(piped_fd[i--]);
			free(piped_fd);
			return (NULL);
		}
		i++;
	}
	return (piped_fd);
}

void	free_pipes(t_data *shell)
{
	int		i;

	i = 0;
	while (i + 1 < shell->cmd_count)
	{
		free(shell->fd[i]);
		i++;
	}
}

void	close_pipes(t_data *shell)
{
	int		i;

	i = 0;
	while (i + 1 < shell->cmd_count)
	{
		close(shell->fd[i][WREND]);
		close(shell->fd[i][RDEND]);
		i++;
	}
}

static void	init_fd(t_data *shell)
{
	shell->fd = NULL;
}

void	init_pipeline(t_data *shell)
{
	shell->pids = (pid_t *)ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		perror("Error pid init\n");
		exit(EXIT_FAILURE);
	}
	init_fd(shell);
	if (shell->cmd_count > 1)
		shell->fd = creating_pipes(shell);
}
