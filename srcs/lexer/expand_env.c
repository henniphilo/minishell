#include "../../incl/minishell.h"

static char *find_limit(char *start)
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

static char	*expand(t_lexer *tokens, char *dollar, char *limit, char *value)
{
	char	*joined;
	char	*end;
	int		len;

	end = ft_strjoin(value, limit);
	if (!end)
		return (error_ptr(ALLOC_ERR));
	*dollar = '\0';
	joined = ft_strjoin(tokens->str, end);
	free(end);
	if (!joined)
		return (error_ptr(ALLOC_ERR));
	len = ft_strlen(tokens->str);
	free(tokens->str);
	tokens->str = joined;
	return (&(joined[len]));
}

static char	*split_expand_join(t_lexer *tokens, char *dollar, char *limit, t_environ *env)
{
	char	*name;
	char	*value;
	char	*tmp;

	name = ft_substr(dollar, 1, limit - dollar); //check if correct
	if (!name)
		return (error_ptr(ALLOC_ERR));
	value = NULL;
	while (env && !value)
	{
		if (ft_strcmp(env->name, name) == 0)
			value = env->value;
		env = env->next;
	}
	tmp = expand(tokens, dollar, limit, value);
	free(name);
	return (tmp);
}

static int	ft_trim_last(t_lexer *tokens)
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

static int	find_and_replace(t_lexer *tokens, t_environ *env)
{
	char	*tmp;
	char	*limit;

	if (!tokens->str)
		return (1);
	tmp = tokens->str;
	while (ft_strchr(tmp, '$'))
	{
		limit = find_limit(ft_strchr(tmp, '$') + 1); //if there is nothing after '$', but a space or a delimiter, it will be printed
		if (limit == ft_strchr(tmp, '$') + 1)
		{
			if (*limit == '\0' && tokens->space_after == 0 && tokens->next)
				return (ft_trim_last(tokens));
			tmp = limit;
		}
		else
			tmp = split_expand_join(tokens, ft_strchr(tmp, '$'), limit, env);
	}
	if (!tmp)
		return (1);
	return (0);
}

static int	expand_tilde(t_lexer *tokens, t_environ *env)
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

/*expands environment variable to their values;
environment variable names consist solely of
uppercase letters, digits, and the <underscore>
and do not begin with a digit. */
int	expand_env(t_lexer *tokens, t_environ *env)
{
	while (tokens)
	{
		while (!(tokens->type == WORD)) //to not expand what comes after a heredoc or redirection
		{
			tokens = tokens->next;
			while (tokens && !(tokens->previous->type == PIPE) && tokens->type == WORD) //check if it segfaults when << is the laste element of the line
			{
				tokens = tokens->next;
				if ( tokens && tokens->space_after == 1)
					break ;
			}
		}
		if (tokens->type == WORD && !(tokens->quote == SINGLE))
		{
			if (!tokens->str) //necessary?
				return (error_int(EXPAN_ERR)); //necessary?
			if (ft_strcmp("~", tokens->str) == 0 && expand_tilde(tokens, env)) //check
				return (error_int(EXPAN_ERR));
			if (ft_strchr(tokens->str, '$'))
			{
				if (find_and_replace(tokens, env))
					return (error_int(EXPAN_ERR));
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

