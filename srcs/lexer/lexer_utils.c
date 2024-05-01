#include "../../incl/minishell.h"

/*checks if token is <<*/
int	check_here(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '<')
		*type = HEREDOC;
	return (0);
}

/*checks if token is >>*/
int	check_append(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '>')
		*type = APPEND;
	return (0);
}

/*checks for syntax errors after lexing, e.g. echo hi ||| ls; | echo*/
int	check_syntax_and_here(t_lexer *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (synt_error_int(PIPE)); //error if first token is a pipe
	while (tokens)
	{
		if (tokens->type == INPUT || tokens->type == OUTPUT || tokens->type == HEREDOC || tokens->type == APPEND || tokens->type == PIPE)
		{
			if (!tokens->next)
				return (error_int(NL_ERR));
		}
		if (tokens->type == PIPE)
		{
			if (tokens->next->type == PIPE)
				return (synt_error_int(PIPE));
		}
		else if (!(tokens->type == WORD))
		{
			if (tokens->next->type == WORD)
			{
				if (tokens->type == HEREDOC)
					//handle_heredoc(); //do this function
				continue ;
			}
			else
				return (synt_error_int(tokens->next->type));
		}
		tokens = tokens->next;
	}
	return (0);
}

/*joins two tokens of type word if the first one is not followed by a space*/
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
			s = ft_strjoin(node->str, node->next->str);
			if (!s)
			{
				free(s);
				return (error_int(ALLOC_ERR));
			}
			if (node->str || node->next->str)
				node->here_quote = 1; //for heredocs
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
