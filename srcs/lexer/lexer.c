#include "../../incl/minishell.h"

int	check_unclosed(char *buf)
{
	int	i;
	int	dbl;
	int	sgl;

	i = 0;
	dbl = 0;
	sgl = 0;
	while (buf[i])
	{
		if (buf[i] == '\"') //but what if "abc'de"efg'h ->need another approach
			dbl++;
		if (buf[i] == '\'')
			sgl++;
		i++;
	}
	if (dbl % 2 || sgl % 2)
		return (1);
	return (0);
}

int	is_space(char c) //shall I check all white spaces or only spaces
{
	return (c == 32);
}

void	lexer(t_data *data)
{
	//what do I do with a commandline consisting of only spaces?
}
