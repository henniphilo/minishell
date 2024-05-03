#include "../../incl/minishell.h"

int	init_cmd_args(t_lexer *tokens, t_command **node)
{
	while (tokens && tokens->type != PIPE)
	{
	/* 	if (tokens->type == HEREDOC)
		{
			tokens = tokens->next;
			//check for syntax error? if !tokens "bash: syntax error near unexpected token `newline'"
			(*node)->delimiter = ft_strdup(tokens->str);
			if (!(*node)->delimiter)
				return (error_int(ALLOC_ERR));
		}
		if (tokens->type == OUTPUT)
		{
			tokens = tokens->next;
			//check for syntax error? if !tokens "bash: syntax error near unexpected token `newline'"
			(*node)->filename = ft_strdup(tokens->str);
			if (!(*node)->delimiter)
				return (error_int(ALLOC_ERR));
		} */
		if (!(tokens->type == WORD)) //later tbd: handling of redirections
			tokens = tokens->next; //later tbd: handling of redirections
		else
			(*node)->args = append_arr((*node)->args, tokens->str); //temporary
		tokens = tokens->next;
	}
	return (0);
}

/*creates a new node*/
t_command	*new_cmd_list(t_lexer *tokens)
{
	t_command	*new_node;

	new_node = ft_calloc(1, sizeof(t_command));
	if (!new_node)
		return (error_ptr(ALLOC_ERR));
	new_node->next = NULL;
	new_node->cmd = ft_strdup(tokens->str);
	if (!new_node->cmd)
	{
		free(new_node);
		return (error_ptr(ALLOC_ERR));
	}
	tokens = tokens->next;
	if (init_cmd_args(tokens, &new_node))
	{
		//free_cmd(new_node); //create function
		return (NULL);
	}
	return (new_node);
}

/*returns the last element of the command list*/
t_command	*cmd_list_last(t_command *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the command list*/
void	cmd_list_add_back(t_command **lst, t_command *new)
{
	t_command	*pos;

	if (lst)
	{
		pos = cmd_list_last(*lst);
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
		while (tokens)
		{
			if (tokens->type == PIPE) //go until pipe
				break;
			tokens = tokens->next;
		}
		if (tokens) //skip pipe
			tokens = tokens->next;
	}
	return (list);
}
