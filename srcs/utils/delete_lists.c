#include "../../incl/minishell.h"

/*frees one element of the token list used for lexing*/
void	delone_tokens(t_lexer *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		free(token);
	}
}

/*frees the token list used for lexing*/
void	free_tokens(t_lexer **tokens)
{
	if (tokens && *tokens)
	{
		free_tokens(&(*tokens)->next);
		delone_tokens(*tokens);
		tokens = NULL;
	}
}

/*frees one element of the token list used for lexing*/
void	delone_env_list(t_environ *env)
{
	if (env)
	{
		if (env->value)
			free(env->value);
		if (env->name)
			free(env->name);
		free(env);
	}
}

/*frees the token list used for lexing*/
void	free_env_list(t_environ **env)
{
	if (env && *env)
	{
		free_env_list(&(*env)->next);
		delone_env_list(*env);
		env = NULL;
	}
}
