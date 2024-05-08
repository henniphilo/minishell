#include "../../incl/minishell.h"

int	ambig_redir_err_int(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (1);
}

int	infile_err_int(char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}


