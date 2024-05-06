#include "../../incl/minishell.h"

/*joining of 3 strings:
the part before the expansion, the expanded value,
and the part after the expansion if they exist*/
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

/*loops through the environment variables and finds the value for the expansion*/
static char	*split_expand_join(t_lexer *tokens, char *dollar, char *limit, t_data *shell)
{
	char		*name;
	char		*value;
	char		*tmp;
	t_environ	*env;

	value = NULL;
	env = shell->env_list;
	if (limit == dollar + 1 && *limit == '?')
	{
		limit++;
		value = ft_itoa(shell->estatus);
		if (!value)
			return (error_ptr(ALLOC_ERR));
	}
	name = ft_substr(dollar, 1, limit - dollar - 1);
	if (!name)
		return (error_ptr(ALLOC_ERR));
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

/*looks for a delimiter and sends the string to expansion if it finds a $*/
static int	find_and_replace(t_lexer *tokens, t_data *shell)
{
	char	*tmp;
	char	*limit;

	if (!tokens->str)
		return (1);
	tmp = tokens->str;
	while (ft_strchr(tmp, '$'))
	{
		limit = find_limit(ft_strchr(tmp, '$') + 1); //if there is nothing after '$', but a space or a delimiter, it will be printed
		if (limit == ft_strchr(tmp, '$') + 1 && !(*limit == '?')) //handle $ before a quote or space
		{
			if (*limit == '\0' && tokens->space_after == 0 && tokens->next)
				return (ft_trim_last(tokens));
			tmp = limit;
		}
		else //handle $ expansion or $?
			tmp = split_expand_join(tokens, ft_strchr(tmp, '$'), limit, shell); //ch
	}
	if (!tmp)
		return (1);
	return (0);
}

/*expands special character ~ to HOME*/
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
int	expand_env(t_lexer *tokens, t_data *shell)
{
	while (tokens)
	{
		if (!(tokens->type == PIPE) && !(tokens->type == WORD)) //to not expand what comes after a heredoc or redirection
		{
			tokens = tokens->next;
			while (tokens && tokens->next && tokens->type == WORD && tokens->space_after == 0) //check if it segfaults when << is the laste element of the line
				tokens = tokens->next;
		}
		else if (tokens->type == WORD && !(tokens->quote == SINGLE) && tokens->str)
		{
			if (ft_strcmp("~", tokens->str) == 0 && expand_tilde(tokens, shell->env_list)) //check
				return (error_int(EXPAN_ERR));
			if (ft_strchr(tokens->str, '$'))
			{
				if (find_and_replace(tokens, shell))
					return (error_int(EXPAN_ERR));
			}
		}
		if (tokens)
			tokens = tokens->next;
	}
	return (0);
}

