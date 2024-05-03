#include "../incl/minishell.h"

static void	print_tokens(t_lexer *tokens)
{
	while (tokens)
	{
		printf("string: %s\ntype: %i\nquote: %i\n", tokens->str, tokens->type, tokens->quote);
		tokens = tokens->next;
	}
}
static void	print_cmds(t_command *cmds)
{
	int i;

	while (cmds)
	{
		printf("command: %s\n", cmds->cmd);
		i = 0;
		if (cmds->args)
		{
			while (cmds->args[i])
			{
				printf("argument %i: ", i);
				printf("%s\n", cmds->args[i]);
				i++;
			}
		}
		i = 0;
		if (cmds->argv)
		{
			while (cmds->argv[i])
			{
				printf("argv[%i]: ", i);
				printf("%s\n", cmds->argv[i]);
				i++;
			}
		}
		cmds = cmds->next;
	}
}

void	test(t_data *shell)
{
	printf("\nLEXER:\n");
	print_tokens(shell->tokens);
	printf("\nPARSER:\n");
	print_cmds(shell->toex);
	printf("\nnumber of pipes: %i\n\n", count_commands(shell->toex));
}
