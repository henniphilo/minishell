#include "../../incl/minishell.h"

int	direc_err(char *str)
{
	ft_putendl_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}

int	cd_error_int(char *s)
{
	if (!s)
		return (1);
	ft_putstr_fd("bash: cd: ", 2);
	if (ft_strcmp("HOME", s) == 0)
	{
		ft_putendl_fd("HOME not set", 2);
		return (1);
	}
	ft_putstr_fd(s, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}
