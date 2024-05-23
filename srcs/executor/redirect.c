/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:37 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:06:53 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	redirect_pipes(t_command *toex)
{
	if (toex->fd_in != -2)
	{
		if (dup2(toex->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in fail");
			close(toex->fd_in);
			g_estatus = 1;
			return ;
		}
		close(toex->fd_in);
	}
	if (toex->fd_out != -2)
	{
		if (dup2(toex->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_out fail");
			close(toex->fd_out);
			g_estatus = 1;
			return ;
		}
		close(toex->fd_out);
	}
}
