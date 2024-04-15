#include "../../incl/minishell.h"

static int	is_space(char c) //shall I check all white spaces or only spaces
{
	return (c == 32);
}

void	lexer(t_data *data)
{
	//what do I do with a commandline consisting of only spaces?
	int	i;

	i = 0;
	while (data->buf[i] == 32)
		i++;
}
