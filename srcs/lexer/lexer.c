#include "../../incl/minishell.h"

/* static int	is_space(char c) //shall I check all white spaces or only spaces
{
	return (c == 32);
} */

t_lexer	*new_list(void)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (NULL);
	new_node->single_quote = 0;
	new_node->str = NULL;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

int	lexer(t_data *data)
{
	char	*tmp_buf;

	//buf = ft_strtrim(data->buf, " ");
	tmp_buf = data->buf;
	data->tokens = new_list();
	if (!data->tokens)
		return (error_int(ALLOC_ERR));
	while (*tmp_buf)
	{
		while (*tmp_buf == 32)
			tmp_buf++;
		if (tmp_buf == '\"' || tmp_buf == '\'')
			//tmp_buf = handle_quotes();
		else if (ft_strchr("<>|", tmp_buf))
			//tmp_buf = handle_meta();
		else if (*tmp_buf)
			//tmp_buf = handle_words();
	}
	return (0);
}

if quote -> find end of quote -> create a substring -> append ->return start of bufferrest
if not quote -> go until space or quote or special character or end of string -> create substring -> append ->return start of bufferrest
