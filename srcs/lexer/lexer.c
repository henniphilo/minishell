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

static t_lexer	*list_last(t_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	list_add_back(t_lexer *lst, t_lexer *new)
{
	t_lexer	*pos;

	pos = list_last(lst);
	if (!pos)
		lst = new;
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
	int		i;

	i = 0;
	while (tmp_buf[0] != tmp_buf[i])
		i++;
	s = ft_substr((const char *)(tmp_buf), 1, i);
	if (!s)
		return (NULL);
	printf("%s", s); //test
	node = new_list(WORD, s, (*tmp_buf == '\''));
	if (!node)
	{
		free (s);
		return (NULL);
	}
	list_add_back(tokens, node);
	return (tmp_buf + i + 1);
}

int	lexer(t_data *data)
{
	char	*tmp_buf;

	tmp_buf = data->buf;
	//buf = ft_strtrim(data->buf, " ");
	//data->tokens = new_list(0, 0, 0);
	//if (!data->tokens)
	//	return (error_int(ALLOC_ERR));
	while (*tmp_buf)
	{
		while (*tmp_buf && *tmp_buf == 32)
			tmp_buf++;
		if (*tmp_buf == '\"' || *tmp_buf == '\'')
			tmp_buf = handle_quotes(tmp_buf, data->tokens);
/* 		else if (ft_strchr("<>|", *tmp_buf))
			//tmp_buf = handle_meta(tmp_buf, );
		else if (*tmp_buf)
			//tmp_buf = handle_words(tmp_buf, data->tokens); */
		if (*tmp_buf)
			tmp_buf++; //test

		if (!tmp_buf)
			return (error_int(ALLOC_ERR));
	}
	printf("%s\n%i", data->tokens->str, data->tokens->type);
	return (0);
}

//if quote -> find end of quote -> create a substring -> append -> return start of bufferrest
//if not quote -> go until space or quote or special character or end of string -> create substring -> append -> return start of bufferrest
