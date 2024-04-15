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

/*c0c7c1% echo hi >>> hello
zsh: parse error near `>'

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

c0c7c1% echo hi >>* hello
zsh: is a directory: incl ///not relevcant for us though

*/
