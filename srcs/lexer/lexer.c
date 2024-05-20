#include "../../incl/minishell.h"

/*stores redirections and pipes
in a node of a tokens linked list
as type PIPE, INPUT, OUTPUT, APPEND or HEREDOC*/
static char	*handle_meta(char *tmp_buf, t_lexer **tokens)
{
	t_lexer	*node;
	t_type	type;

	type = 0;
	if (*tmp_buf == '|')
		type = PIPE;
	else if (*tmp_buf == '<')
	{
		type = INPUT;
		if (check_here(&type, tmp_buf))
			return (NULL);
	}
	else if (*tmp_buf == '>')
	{
		type = OUTPUT;
		if (check_append(&type, tmp_buf))
			return (NULL);
	}
	node = new_lex_list(type, NULL, NULL, NULL);
	if (!node)
		return (NULL);
	lex_list_add_back(tokens, node);
	if (tmp_buf[0] == tmp_buf[1] && (tmp_buf[1] == '<' || tmp_buf[1] == '>'))
		tmp_buf++;
	return (tmp_buf + 1);
}

/*stores the everything between quotes as string
and the type of the quote as boolean
in a node of a tokens linked list as type WORD*/
static char	*handle_quotes(char *tmp_buf, t_lexer **tokens)
{
	t_lexer	*node;
	char	*s;
	int		i;

	i = 1;
	while (tmp_buf[0] != tmp_buf[i])
		i++;
	if (i == 1)
		s = ft_strdup("");
	else
		s = ft_substr((const char *)(tmp_buf), 1, i - 1);
	if (!s)
		return (NULL);
	node = new_lex_list(WORD, s, (*tmp_buf == '\''), (*tmp_buf == '\"'));
	if (!node)
	{
		free (s);
		return (NULL);
	}
	if (tmp_buf[i + 1] == 32)
		node->space_after = 1;
	lex_list_add_back(tokens, node);
	return (tmp_buf + i + 1);
}

/*stores the everything delimited by spaces
 or special character or quotes as string
in a node of a tokens linked list as type WORD*/
static char	*handle_words(char *tmp_buf, t_lexer **tokens)
{
	int		i;
	char	*s;
	t_lexer	*node;

	i = 0;
	while (tmp_buf[i] && !(ft_strchr("|<>\'\"\t ", tmp_buf[i])))
		i++;
	s = ft_substr((const char *)(tmp_buf), 0, i);
	if (!s)
		return (NULL);
	node = new_lex_list(WORD, s, NULL, NULL);
	if (!node)
	{
		free (s);
		return (NULL);
	}
	if (tmp_buf[i] == 32 || tmp_buf[i] == 9)
		node->space_after = 1;
	lex_list_add_back(tokens, node);
	return (tmp_buf + i);
}

/*checks for empty expansions or tokens that were
not between quotes and deletes them from the list*/
static void	check_empty_tokens(t_data *shell)
{
	t_lexer	*tokens;

	tokens = shell->tokens;
	if (tokens->type == WORD)
	{
		if (tokens->str && tokens->str[0] == '\0' && tokens->quote == NONE)
		{
			if (tokens->previous)
				tokens->previous->next = tokens->next->next;
			else
				shell->tokens = tokens->next;
			if (tokens->next)
				tokens->next->previous = tokens->previous;
			delone_tokens(tokens);
		}
	}
}

/*where the lexing happens, returns 1 on error,
processes quotes first, then the special characters
like pipes or redirections and then the rest*/
int	lexer(t_data *shell)
{
	char	*tmp_buf;

	tmp_buf = shell->buf;
	while (*tmp_buf)
	{
		if (*tmp_buf == 32 || *tmp_buf == 9)
			tmp_buf++;
		else if (*tmp_buf == '\"' || *tmp_buf == '\'')
			tmp_buf = handle_quotes(tmp_buf, &shell->tokens);
		else if (ft_strchr("<>|", *tmp_buf))
			tmp_buf = handle_meta(tmp_buf, &shell->tokens);
		else if (*tmp_buf)
			tmp_buf = handle_words(tmp_buf, &shell->tokens);
		if (!tmp_buf)
			return (error_int(LEX_ERR));
	}
	if (expand_env(shell->tokens, shell))
		return (1);
	if (join_words(shell) || check_syntax_and_here(shell->tokens, shell))
		return (1);
	check_empty_tokens(shell);
	shell->cmd_count = count_commands(shell->tokens);
	return (0);
}

