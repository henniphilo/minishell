#include "../../incl/minishell.h"

/*creates a new node*/
static t_lexer	*new_list(t_type t, char *s, bool q)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->double_quote = q;
	new_node->type = t;
	new_node->str = s;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

/*returns the last element of the token list*/
static t_lexer	*list_last(t_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the token list*/
static void	list_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*pos;

	pos = list_last(*lst);
	if (!pos)
		*lst = new;
	else
	{
		pos->next = new;
		new->previous = pos;
	}
}

static char	*handle_meta(char *tmp_buf, t_lexer **tokens)
{
	if (*tmp_buf = "|")
	else if (*tmp_buf = "<")
	else if (*tmp_buf = ">")

}

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
	node = new_list(WORD, s, (*tmp_buf == '\"'));
	if (!node)
	{
		free (s);
		return (NULL);
	}
	if (tmp_buf + i + 1 == 32)
		node->space_after = 1;
	list_add_back(tokens, node);
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
		else if (ft_strchr("<>|", *tmp_buf))
			tmp_buf = handle_meta(tmp_buf, &data->tokens);
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
