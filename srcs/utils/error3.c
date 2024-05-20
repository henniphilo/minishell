#include "../../incl/minishell.h"

int	direc_err(char *str)
{
	ft_putendl_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}
