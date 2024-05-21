/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:10:21 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/21 17:10:22 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*creates a new node*/
t_lexer	*new_lex_list(t_type t, char *s, bool sq, bool dq)
{
	t_lexer	*new_node;

	new_node = ft_calloc(1, sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	if (sq == 1)
		new_node->quote = SINGLE;
	if (dq == 1)
		new_node->quote = DOUBLE;
	new_node->type = t;
	new_node->str = s;
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
