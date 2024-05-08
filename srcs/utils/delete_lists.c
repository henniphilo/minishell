#include "../../incl/minishell.h"

/*frees the command list used for parsing*/
void	free_commands(t_command **cmds)
{
	if (cmds && *cmds)
	{
		free_commands(&(*cmds)->next);
		delone_commands(*cmds);
		*cmds = NULL;
	}
}

/*frees one element of the command list used for parsing*/
void	delone_commands(t_command *cmds)
{
	if (cmds)
	{
		if (cmds->cmd)
			free(cmds->cmd);
		free_arr(cmds->args, cmds->argv);
		free_redirs(&(cmds->redirs));
		free(cmds);
	}
}

/*frees one element of the token list used for lexing*/
void	delone_tokens(t_lexer *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->ambig_redir)
			free(token->ambig_redir);
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
		*tokens = NULL;
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
		env = NULL;
	}
}

/*frees the token list used for lexing*/
void	free_env_list(t_environ **env)
{
	if (env && *env)
	{
		free_env_list(&(*env)->next);
		delone_env_list(*env);
		*env = NULL;
	}
}
