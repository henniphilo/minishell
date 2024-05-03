#include "../../incl/minishell.h"

static int	init_cmd_args(t_lexer *tokens, t_command **node)
{
	while (tokens && tokens->type != PIPE)
	{
	/* 	if (tokens->type == HEREDOC)
		{
			tokens = tokens->next;
			//check for syntax error? if !tokens "bash: syntax error near unexpected token `newline'"
			(*node)->delimiter = ft_strdup(tokens->str);
			if (!(*node)->delimiter)
				return (error_int(ALLOC_ERR));
		}
		if (tokens->type == OUTPUT)
		{
			tokens = tokens->next;
			//check for syntax error? if !tokens "bash: syntax error near unexpected token `newline'"
			(*node)->filename = ft_strdup(tokens->str);
			if (!(*node)->delimiter)
				return (error_int(ALLOC_ERR));
		} */
		(*node)->args = append_arr((*node)->args, tokens->str); //temporary
		tokens = tokens->next;
	}
	return (0);
}

static int	init_argv(t_data *shell)
{
	int		i;

	if (!shell->toex->cmd)
		return (0);
	shell->toex->argv = ft_calloc(array_len(shell->toex->args) + 1, sizeof(char *));
	if (!shell->toex->argv)
		return (error_int(ALLOC_ERR));
	shell->toex->argv[0] = ft_strdup(shell->toex->cmd);
	if (!shell->toex->argv[0])
		return (error_int(ALLOC_ERR));
	i = 1;
	while (shell->toex->args[i - 1])
	{
		shell->toex->argv[i] = ft_strdup(shell->toex->args[i - 1]);
		if (!shell->toex->argv[i])
			return (error_int(ALLOC_ERR));
	}
}

int	parser(t_data *shell)
{
	shell->toex = create_cmdlist(shell->tokens);
	if (!shell->toex)
		return (error_int(PARSE_ERR));
	if (!init_argv(shell))
		return (error_int(PARSE_ERR));
	return (0);
}
