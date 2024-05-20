#include "../../incl/minishell.h"

int	ambig_redir_err_int(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (1);
}

int	file_err_int(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
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
	return (1); //exit code 1
}

int	command_err(char *cmd)
{
	if (cmd)
		ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}


