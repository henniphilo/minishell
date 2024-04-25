#include "../../incl/minishell.h"


static char *find_limit(char *dollar)
{
	while (*dollar)
	{
		if (!(*dollar >))
		dollar++;
	}
}

int	find_and_replace(char **str)
{
	char	*tmp;
	char	*dollar;
	char	*limit;
	char	*name;
	char	*value;

	tmp = NULL;
	if (!str)
		return (-1);
	dollar = ft_strchr(str, '$');
	limit = find_limit(dollar);
	name = ft_substr(dollar, 1, limit - dollar);
	if (!name)
		return (-1);
	tmp = split_expand_join(str, dollar, limit);
	free(*str);
	return(ft_strlen((const char *)value));
}

void	expand_env(t_lexer *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == WORD && !(tokens->single_quote))
		{
			if (i = -1 && !tokens->str)
				return (NULL);
			while (ft_strchr(&(tokens->str[i]), '$'))
				i = find_and_replace(&(tokens->str));
		}
		tokens = tokens->next;
	}
}
