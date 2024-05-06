#include "../../incl/minishell.h"

/*creates a new redirection node*/
static t_redir	*new_redir_list(t_lexer *tokens)
{
	t_redir	*new_node;

	new_node = ft_calloc(1, sizeof(t_redir));
	if (!new_node)
		return (error_ptr(ALLOC_ERR));
	new_node->file = ft_strdup(tokens->str);
	if (!new_node->file)
	{
		free (new_node);
		return (error_ptr(ALLOC_ERR));
	}
	new_node->type = tokens->previous->type;
	return (new_node);
}

/*returns the last element of the redirection list*/
static t_redir	*redir_list_last(t_redir *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the redirection list*/
static void	redir_list_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*pos;

	if (lst)
	{
		pos = redir_list_last(*lst);
		if (!pos)
			*lst = new;
		else
			pos->next = new;
	}
}

/*adds a redirection node to the redirection list*/
int	add_redir(t_lexer *tokens, t_command *toex)
{
	t_redir	*node;

	node = new_redir_list(tokens->next);
	if (!node)
		return (1);
	redir_list_add_back(&(toex->redirs), node);
	return (0);
}

//add a free function!!!
