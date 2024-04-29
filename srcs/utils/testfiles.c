#include "../../incl/minishell.h"

static void	print_tokens(tokens)
{
 	t_lexer	*tokens = data->tokens;
	while (tokens)
	{
		printf("string: %s\ntype: %i\nsinglequote: %d\n", tokens->str, tokens->type, tokens->single_quote);
		tokens = tokens->next;
	}
}

void	test(t_data *data)
{
	print_tokens(data->tokens);
}
