/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:05:01 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/23 12:03:04 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ambig_redir_err_int(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (1);
}

int	file_err_int(t_data *shell, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	g_estatus = 1;
	shell->bi_check = 1;
	return (1);
}

int	eof_error(char *delimiter, int linenum)
{
	char	*line;

	line = ft_itoa(linenum);
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(" delimited by end-of-file ", 2);
	ft_putstr_fd("(wanted '", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	free(delimiter);
	free(line);
	return (0);
}

int	ident_error_int(char *ident)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(ident, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	command_err(char *cmd, char *s, int ret, char *path)
{
	if (cmd)
		ft_putstr_fd(cmd, 2);
	if (path)
	{
		free(path);
		path = NULL;
	}
	if (s)
		ft_putendl_fd(s, 2);
	return (ret);
}
