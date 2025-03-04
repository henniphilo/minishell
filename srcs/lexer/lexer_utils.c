/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:03 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/21 17:14:04 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*checks if token is <<*/
int	check_here(t_type *type, char *buf)
{
	if (buf[1] == '<')
		*type = HEREDOC;
	return (0);
}

/*checks if token is >>*/
int	check_append(t_type *type, char *buf)
{
	if (buf[1] == '>')
		*type = APPEND;
	return (0);
}

/*checks for syntax errors after lexing, e.g. echo hi ||| ls; >< file*/
int	check_syntax_and_here(t_lexer *tokens, t_data *shell)
{
	if (tokens && tokens->type == PIPE)
		return (synt_error_int(PIPE));
	while (tokens)
	{
		if (!(tokens->type == WORD))
		{
			if (!tokens->next)
				return (error_int(NL_ERR));
		}
		if (tokens->type == PIPE)
		{
			if (tokens->next->type == PIPE)
				return (synt_error_int(PIPE));
		}
		else if (!(tokens->type == WORD))
		{
			if (!(tokens->next->type == WORD))
				return (synt_error_int(tokens->next->type));
			if (tokens->type == HEREDOC && handle_heredoc(tokens->next, shell))
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	join_helper(t_lexer *node, t_lexer **next)
{
	char	*s;

	s = ft_strjoin(node->str, node->next->str);
	if (!s)
		return (error_int(ALLOC_ERR));
	free(node->str);
	node->str = s;
	if (!(node->quote == NONE && node->next->quote == NONE))
		node->quote = HERE;
	if (node->next->space_after == 1)
		node->space_after = 1;
	(*next) = node->next->next;
	delone_tokens(node->next);
	if (*next)
		(*next)->previous = node;
	node->next = (*next);
	return (0);
}

/*joins two tokens of type word if the first one is not followed by a space*/
int	join_words(t_data *data)
{
	t_lexer	*node;
	t_lexer	*next;

	node = data->tokens;
	next = NULL;
	while (node)
	{
		while (node->next && node->type == WORD
			&& node->next->type == WORD && node->space_after == 0)
		{
			if (join_helper(node, &next))
				return (1);
		}
		node = node->next;
	}
	return (0);
}
