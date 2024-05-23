/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:33:46 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/23 18:11:10 by hwiemann         ###   ########.fr       */
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

//memory leak wenn program nicht ausfuehrbar bei ""
char	*path_finder(char *cmd, t_data *shell)
{
	char	**path_components;
	char	*current_path;
	char	*full_path;
	int		i;

	i = 0;
	path_components = get_path_components(shell);
	if (path_components == NULL)
		return (NULL);
	while (path_components[i] != NULL)
	{
		current_path = ft_strjoin(path_components[i], "/");
		if (current_path == NULL)
		{
			free_split(path_components);
			free(current_path);
			return (NULL);
		}
		full_path = ft_strjoin(current_path, cmd);
		free(current_path);
		if (full_path == NULL)
		{
			free_split(path_components);
			return (NULL);
		}
		if (access(full_path, F_OK) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free_split(path_components);
				return (full_path);
			}
			else
			{
				free(full_path);
				free_split(path_components);
				return (NULL);
			}
		}
		free (full_path);
		i++;
	}
	free_split(path_components);
	return (cmd);
}
