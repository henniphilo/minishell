#include "../incl/minishell.h"

static void	print_tokens(t_lexer *tokens)
{
	printf("TOKENIZER:\n");
	while (tokens)
	{
		printf("string: %s\ntype: %i\nsinglequote: %d\n", tokens->str, tokens->type, tokens->single_quote);
		tokens = tokens->next;
	}
}
static void	print_cmds(t_command *cmds)
{
	printf("\nPARSER:\n");
	while (cmds)
	{
		printf("command: %s\n", cmds->cmd);
		int i = 0;
		while (cmds->args && cmds->args[i])
		{
			printf("argument %i: ", i);
			printf("%s\n", cmds->args[i]);
			i++;
		}
		cmds = cmds->next;
	}
}

void	test(t_data *shell)
{
	print_tokens(shell->tokens);
	print_cmds(shell->toex);
}
