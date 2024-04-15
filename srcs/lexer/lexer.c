#include "../../incl/minishell.h"

/* static int	is_space(char c) //shall I check all white spaces or only spaces
{
	return (c == 32);
} */

static t_lexer	*new_list(t_type t, char *s, bool q)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (NULL);
	new_node->single_quote = q;
	new_node->type = t;
	new_node->str = s;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

static void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*pos;

	pos = ft_lstlast(*lst);
	if (!pos)
		*lst = new;
	else
	{
		pos->next = new;
		new->previous = pos;
	}
}

static char	*handle_quotes(char *tmp_buf, t_lexer *tokens)
{
	t_lexer	*node;
	char	*s;
	char	i;

	i = 0;
	while (*tmp_buf != tmp_buf[i])
		i++;
	s = ft_substr((const char *)(tmp_buf), 1, i);
	if (!s)
		return (NULL);
	printf("%s", s); //test
	node = new_list(WORD, s, (*tmp_buf == '\''));
	if (!node)
		return (NULL);
	list_add_back(tokens, node);
	return (tmp_buf + i + 1);
}

int	lexer(t_data *data)
{
	char	*tmp_buf;

	//buf = ft_strtrim(data->buf, " ");
	tmp_buf = data->buf;
	//data->tokens = new_list(0, 0, 0);
	//if (!data->tokens)
	//	return (error_int(ALLOC_ERR));
	while (*tmp_buf)
	{
		while (*tmp_buf == 32)
			tmp_buf++;
		if (*tmp_buf == '\"' || *tmp_buf == '\'')
			tmp_buf = handle_quotes(tmp_buf, data->tokens);
		else if (ft_strchr("<>|", *tmp_buf))
			//tmp_buf = handle_meta(tmp_buf, );
		else if (*tmp_buf)
			//tmp_buf = handle_words(tmp_buf, data->tokens);
		if (!tmp_buf)
			return (error_int(ALLOC_ERR));
	}
	return (0);
}

if quote -> find end of quote -> create a substring -> append -> return start of bufferrest
if not quote -> go until space or quote or special character or end of string -> create substring -> append -> return start of bufferrest
