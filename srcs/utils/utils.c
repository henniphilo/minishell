#include "../../incl/minishell.h"

/*calculates the size of a 2D-array*/
int	array_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}
