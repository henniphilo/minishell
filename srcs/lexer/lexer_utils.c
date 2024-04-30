#include "../../incl/minishell.h"

/*function to handle syntax errors*/
int	check_pipe(char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '|')
		return (error_int(PIPE_ERR));
	return (0);
}

int	check_here(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '<')
		*type = HEREDOC;
	return (0);
}

int	check_append(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '>')
		*type = APPEND;
	return (0);
}

int	check_syntax_error(t_lexer *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (error_int(PIPE_ERR)); //error if first token is a pipe
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			if (!tokens->next)
				return (error_int(PIPE_ERR));
			else
			{
				if (tokens->next->type == PIPE)
					return (error_int(PIPE_ERR));
			}
		}
		if (tokens->type == INPUT)
		{

		}
		if (tokens->type == OUTPUT)
		{

		}
		tokens = tokens->next;
	}
}

int	join_words(t_data *data)
{
	t_lexer	*node;
	t_lexer	*next;
	char	*s;

	node = data->tokens;
	next = NULL;
	//if (!node)
	//	return (1);
	while (node)
	{
		while (node->next && node->type == WORD && node->next->type == WORD && node->space_after == 0)
		{
			//take care of heredocs, so do not join if single or double quote comes after <<
			s = ft_strjoin(node->str, node->next->str);
			if (!s)
			{
				free(s);
				return (error_int(ALLOC_ERR));
			}
			free(node->str);
			node->str = s;
			if (node->next->space_after == 1)
				node->space_after = 1;
			next = node->next->next;
			delone_tokens(node->next);
			if (next)
				next->previous = node;
			node->next = next;
		}
		node = node->next;
	}
	return (0);
}
