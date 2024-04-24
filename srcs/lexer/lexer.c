#include "../../incl/minishell.h"

/* static char	*handle_meta(char *tmp_buf, t_lexer **tokens)
{
	if (*tmp_buf = "|")
		edges_pipe(); //handle edge cases
	else if (*tmp_buf = "<")
		edges_less()
	else if (*tmp_buf = ">")
		edges_more();
} */

/*stores the everything between quotes as string
and the type of the quote as boolean
in a node of a tokens linked list as type WORD*/
static char	*handle_quotes(char *tmp_buf, t_lexer **tokens)
{
	t_lexer	*node;
	char	*s;
	int		i;

	i = 1;
	while (tmp_buf[0] != tmp_buf[i])
		i++;
	s = ft_substr((const char *)(tmp_buf), 1, i - 1);
	if (!s)
		return (NULL);
	node = new_lex_list(WORD, s, (*tmp_buf == '\"'));
	if (!node)
	{
		free (s);
		return (NULL);
	}
	if (tmp_buf[i + 1] == 32)
		node->space_after = 1;
	lex_list_add_back(tokens, node);
	return (tmp_buf + i + 1);
}

/*where the lexing happens, returns 1 on error,
processes quotes first, then the special characters
like pipes or redirections and then the rest*/
int	lexer(t_data *data)
{
	char	*tmp_buf;

	tmp_buf = data->buf;
	while (*tmp_buf)
	{
		if (*tmp_buf == 32)
			tmp_buf++;
		else if (*tmp_buf == '\"' || *tmp_buf == '\'')
			tmp_buf = handle_quotes(tmp_buf, &data->tokens);
		//else if (ft_strchr("<>|", *tmp_buf))
		//	tmp_buf = handle_meta(tmp_buf, &data->tokens);
		else if (*tmp_buf)
			tmp_buf++; //test
			//tmp_buf = handle_words(tmp_buf, data->tokens);

		if (!tmp_buf)
			return (error_int(ALLOC_ERR));
	}
	//printf("string: %s\ntype: %i\nsinglequote: %d\n", data->tokens->str, data->tokens->type, data->tokens->single_quote);
	return (0);
}

//if quote -> find end of quote -> create a substring -> append -> return start of bufferrest
//if not quote -> go until space or quote or special character or end of string -> create substring -> append -> return start of bufferrest
//next: expand environmental vars and join chains of WORDs
