/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:24:21 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:11:48 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	var_check(t_data *shell, char *to_check)
{
	t_environ	*check;

	check = find_name_in_envlist(shell, to_check);
	if (!check)
		return (1);
	return (0);
}

void	free_split(char **split_components)
{
	int		i;

	i = 0;
	if (split_components == NULL)
		return ;
	while (split_components[i])
	{
		free(split_components[i]);
		i++;
	}
	free(split_components);
}

int	valid_fd_in_out_check(t_data *shell, t_command *toex)
{
	if (toex->fd_in == -1 || toex->fd_out == -1)
	{
		shell->bi_check = 1;
		g_estatus = 1;
		return (1);
	}
	else
		shell->bi_check = 0;
	return (0);
}
