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
		ft_putendl_fd("wrong input: unclosed quotes", 2);
		return (1);
	}
	i = 0;
	while (buf[i] == 32) //check spaces
		i++;
	if (buf[i] == '\0')
		return (1);
	return (0);
}

/*c0c7c1% echo hi >>> hello
zsh: parse error near `>'
bash: syntax error near unexpected token `>'

c0c7c1% echo hi >>< hello
zsh: parse error near `<'

echo hi <<<< hello
zsh: parse error near `<'

Kein error: c0c7c1% echo hi <<< hello // ?????
hi

c0c7c1% echo hi >>> hello
zsh: parse error near `>'

c0c7c1% echo hi >>. hello
zsh: is a directory: .
bash: .: Is a directory

c0c7c1% echo hi >>* hello
zsh: is a directory: incl ///not relevant for us though

command||command
*/
