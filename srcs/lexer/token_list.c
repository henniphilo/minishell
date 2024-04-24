#include "../../incl/minishell.h"

/*creates a new node*/
t_lexer	*new_lex_list(t_type t, char *s, bool q)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->single_quote = q;
	new_node->type = t;
	new_node->str = s;
	new_node->next = NULL;
	new_node->previous = NULL;
	return (new_node);
}

/*returns the last element of the token list*/
t_lexer	*lex_list_last(t_lexer *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the token list*/
void	lex_list_add_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*pos;

	if (lst)
	{
		pos = lex_list_last(*lst);
		if (!pos)
			*lst = new;
		else
		{
			pos->next = new;
			new->previous = pos;
		}
	}
}
