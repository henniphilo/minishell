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


