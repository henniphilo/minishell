#include "../../incl/minishell.h"

/*finds the delimiter of the expansion,
being a different character than capital letters, digits or '?'*/
char	*find_limit(char *start)
{
	if (*start && *start >= 48 && *start <= 57)
		return (start);
	while (*start)
	{
		if ((*start >= 48 && *start <= 57) || (*start >= 65 && *start <= 90)
			|| (*start >= 97 && *start <= 122) || *start == 95)
			start++;
		else
			return (start);
	}
	return (start);
}

/*if $ is the last character before a quote, it will be removed*/
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

char	*expand_estatus(t_lexer *tokens, char *dollar, char *limit, int estatus)
{
	char	*value;
	char	*ret;

	value = ft_itoa(estatus);
	if (!value)
		return (error_ptr(ALLOC_ERR));
	ret = expand(tokens, dollar, limit, value);
	free(value);
	return (ret);
}

/*expands special character ~ to HOME*/
int	expand_tilde(t_lexer *tokens, t_environ *env)
{
	if (tokens->quote == NONE && ft_strcmp("~", tokens->str) == 0)
	{
		free(tokens->str);
		tokens->str = NULL;
		while (env)
		{
			if (ft_strcmp("HOME", env->name))
			{
				tokens->str = ft_strdup(env->value);
				if (!tokens->str)
					return (error_int(ALLOC_ERR));
				return (0);
			}
			env = env->next;
		}
	}
	return (0);
}
