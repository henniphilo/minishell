/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:46 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/24 12:44:17 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_path(char *path)
{
	if (path != NULL)
		printf("path: %s\n", path);
}

char	**get_path_components(t_data *shell)
{
	int		i;
	char	**path_components;

	i = 0;
	path_components = NULL;
	if (var_check(shell, "PATH") == 0)
	{
		while (shell->env[i] && ft_strnstr(shell->env[i], "PATH=", 5) == 0)
			i++;
		if (shell->env[i])
			path_components = ft_split(shell->env[i] + 5, ':');
	}
	return (path_components);
}

static void	*free_free(char **split, char *to_free)
{
	if (split)
		free_split(split);
	if (to_free)
		free(to_free);
	return (NULL);
}

static char	*get_full_path(char **path_cmps, int i, char **fp, char *cmd)
{
	char	*current_path;

	current_path = ft_strjoin(path_cmps[i], "/");
	if (current_path == NULL)
		return (free_free(path_cmps, current_path));
	*fp = ft_strjoin(current_path, cmd);
	free(current_path);
	if (*fp == NULL)
		return (free_free(path_cmps, NULL));
	return ((*fp));
}

char	*path_finder(char *cmd, t_data *shell, int i)
{
	char	**path_components;
	char	*full_path;

	path_components = get_path_components(shell);
	if (path_components == NULL)
		return (NULL);
	while (path_components[i] != NULL)
	{
		if (get_full_path(path_components, i, &full_path, cmd) == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free_split(path_components);
				return (full_path);
			}
			else
				return (free_free(path_components, full_path));
		}
		free (full_path);
		i++;
	}
	free_split(path_components);
	return (cmd);
}
