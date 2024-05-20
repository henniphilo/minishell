#include "../../incl/minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i++]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (2);
		}
	}
	return (0);
}
