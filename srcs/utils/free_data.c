#include "../../incl/minishell.h"

void	delone_tokens(t_lexer *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		free(token);
	}
}

void	free_tokens(t_lexer **tokens)
{
	if (tokens && *tokens)
	{
		free_tokens(&(*tokens)->next);
		delone_tokens(*tokens);
		tokens = NULL;
	}
}

void	free_env(char **env)
{
	int	i;

	if (env)
	{
		i = -1;
		while (env[++i])
			free(env[i]);
		free(env);
	}
}

void	*free_data(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->buf)
			free(data->buf);
		if (data->fd)
			free(data->fd);
		if (data->bi)
			free(data->bi);
		if (data->arguments)
		{
			i = -1;
			while (data->arguments[++i])
				free(data->arguments[i]);
			free(data->arguments);
		}
		free_tokens(&(data->tokens));
		free_env(data->env);
		free(data);
	}
	return (NULL);
}
