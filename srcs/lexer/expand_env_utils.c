#include "../../incl/minishell.h"

/*finds the delimiter of the expansion, being a different character than capital letters,*/
char *find_limit(char *start)
{
	if (*start && *start >= 48 && *start <= 57)
		return (start);
	while (*start)
	{
		if ((*start >= 48 && *start <= 57) || (*start >= 65 && *start <= 90) || *start == 95)
			start++;
		else
			return (start);
	}
	return (start);
}

/*if $ is the last character before a quote, it gets removed*/
int	ft_trim_last(t_lexer *tokens)
{
	char	*str;
	int		len;

	len = ft_strlen(tokens->str);
	str = ft_calloc(len, 1);
	if (!tokens->str)
		return (error_int(ALLOC_ERR));
	ft_memmove(str, tokens->str, len - 1);
	free(tokens->str);
	tokens->str = str;
	return (0);
}
