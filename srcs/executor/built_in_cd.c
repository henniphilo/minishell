/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:13:07 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/24 16:21:28 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	bi_cd(t_data *shell)
{
	char	*home_path;

	if (shell->toex->args == NULL)
	{
		if (var_check(shell, "HOME"))
			return (cd_error_int("HOME"));
		home_path = find_in_env("HOME");
		chdir(home_path);
		update_old_pwd(shell);
		return (0);
	}
	if (shell->toex->argv[1] && !shell->toex->argv[2])
	{
		if (shell->toex->args[0][0] == '\0'
			|| ft_strcmp(".", shell->toex->args[0]) == 0)
			return (0);
		if (chdir(shell->toex->args[0]) == 0)
		{
			update_old_pwd(shell);
			return (0);
		}
	}
	else
		return (cd_error_int("MANY"));
	return (cd_error_int(shell->toex->args[0]));
}

void	update_envlist(t_data *shell, char *to_up, char *new)
{
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if (ft_strcmp(to_up, head->name) == 0)
		{
			head = replace_value(head, new);
			break ;
		}
		head = head->next;
	}
}

void	update_old_pwd(t_data *shell)
{
	char		*new_pwd;
	char		*old_pwd;
	char		cwd[1024];
	t_environ	*old_pwd_ptr;

	if (var_check(shell, "PWD") == 0)
	{
		old_pwd_ptr = find_name_in_envlist(shell, "PWD");
		old_pwd = ft_strdup(old_pwd_ptr->value);
		if (!old_pwd_ptr->value)
			return ;
		if (var_check(shell, "OLDPWD") == 0)
			update_envlist(shell, "OLDPWD", old_pwd);
		else
			free(old_pwd);
		new_pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
		if (!new_pwd)
			return ;
		shell->pwd = ft_strdup(new_pwd);
		update_envlist(shell, "PWD", new_pwd);
	}
}

t_environ	*find_name_in_envlist(t_data *shell, char *name)
{
	t_environ	*head;

	head = shell->env_list;
	while (head != NULL)
	{
		if (ft_strcmp(name, head->name) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_environ	*find_name_in_exportlist(t_environ *export_list, char *name)
{
	while (export_list != NULL)
	{
		if (ft_strcmp(name, export_list->name) == 0)
			return (export_list);
		export_list = export_list->next;
	}
	return (NULL);
}
