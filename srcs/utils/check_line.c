#include "../../incl/minishell.h"

static int	check_unclosed(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\"')
		{
			i++;
			while (buf[i] && buf[i] != '\"')
				i++;
			if (buf[i] == '\0')
				return (1);
		}
		if (buf[i] == '\'')
		{
			i++;
			while (buf[i] && buf[i] != '\'')
				i++;
			if (buf[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_line(char *buf)
{
	int	i;

	if (check_unclosed(buf))
	{
		printf("wrong input: unclosed quotes\n");
		return (1);
	}
	i = 0;
	while (buf[i] == 32)
		i++;
	if (buf[i] == '\0')
		return (1);
	return (0);
}
