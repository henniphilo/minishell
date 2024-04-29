#include "../../incl/minishell.h"

/* t_command	*init_cmd_node(t_lexer *tokens, t_command *new_node)
{
	t_command	*node;

	node = new_node;

	if (!node->cmd)
	{
		free(n)
	}


	return (node);
} */

/*creates a new node*/
t_command	*new_cmd_list(t_lexer *tokens)
{
	t_command	*new_node;

	new_node = ft_calloc(1, sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->cmd = ft_strdup(tokens->str);
	if (!new_node->cmd)
	{
		free(new_node);
		return (NULL);
	}
	tokens = tokens->next;
	return (new_node);
}

/*returns the last element of the token list*/
t_lexer	*cmd_list_last(t_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the token list*/
void	cmd_list_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*pos;

	if (lst)
	{
		pos = lex_list_last(*lst);
		if (!pos)
			*lst = new;
		else
			pos->next = new;
	}
}

t_command	*create_cmdlist(t_lexer *tokens)
{
	t_command	*list;
	t_command	*node;

	list = NULL;
	node = NULL;
	while (tokens)
	{
		node = new_cmd_list(tokens);
		if (!node)
			return (NULL);
		cmd_list_add_back(&list, node);
		while (tokens && tokens->type != PIPE) //go until pipe
			tokens = tokens->next;
		if (tokens->next) //skip pipe
			tokens = tokens->next;
	}
	return (list);
}

int	parser(t_data *data)
{
	data->commands = create_cmdlist(data->tokens);
	if (!data->commands)
		return (error_int(PARSE_ERR));
	return (0);
}
