#include "../../incl/minishell.h"

static char	*find_and_replace(char *str)
{
	char	*tmp;
	char	*dollar;

	tmp = NULL;
	if (!str)
		return (NULL);
	if (!ft_strchr(str, '$'))
		return (str);
	else
	{
		dollar = ft_strchr(str, '$');
		return (find_and_replace(tmp));
	}

}

void	expand_env(t_lexer **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->type == WORD && !((*tokens)->single_quote))
			(*tokens)->str = find_and_replace((*tokens)->str);
		*tokens = (*tokens)->next;
	}
}
