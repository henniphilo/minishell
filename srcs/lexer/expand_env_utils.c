/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:10:33 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/21 17:10:34 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*finds the delimiter of the expansion,
being a different character than capital letters, digits or '?'*/
char	*find_limit(char *start)
{
	if (*start && *start >= 48 && *start <= 57)
		return (start);
	while (*start)
	{
		if ((*start >= 48 && *start <= 57) || (*start >= 65 && *start <= 90)
			|| (*start >= 97 && *start <= 122) || *start == 95)
			start++;
		else
			return (start);
	}
	return (start);
}

/*if $ is the last character before a quote, it will be removed*/
int	ft_trim_last(t_lexer *tokens)
{
	char	*str;
	int		len;

	len = ft_strlen(tokens->str);
	str = ft_calloc(len, 1);
	if (!tokens->str)
		return (error_int(ALLOC_ERR));
	ft_memmove(str, tokens->str, len - 1);
	free(tokens->str);
	tokens->str = str;
	return (0);
}

char	*expand_estatus(t_lexer *tokens, char *dollar, char *limit)
{
	char	*value;
	char	*ret;

	value = ft_itoa(g_estatus);
	if (!value)
		return (error_ptr(ALLOC_ERR));
	ret = expand(tokens, dollar, limit, value);
	free(value);
	return (ret);
}

/*expands special character ~ to HOME*/
int	expand_tilde(t_lexer *tokens, char *home)
{
	if (tokens->quote == NONE)
	{
		free(tokens->str);
		tokens->str = ft_strdup(home);
		if (!tokens->str)
			return (error_int(ALLOC_ERR));
	}
	return (0);
}
