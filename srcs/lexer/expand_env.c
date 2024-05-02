#include "../../incl/minishell.h"


static char *find_limit(char *start)
{
	if (start && *start >= 48 && start <= 57)
		return (start);
	while (start)
	{
		if ((*start >= 48 && start <= 57) || (*start >= 65 && *start <= 90) || *start == 95)
			start++;
		else
			return (start);
	}
	return (start);
}

static char	*split_expand_join(char **str, char *dollar, char *limit, t_environ *env)
{
	char *name;

	while (env)
	{
		if (env->name == ft_strcmp()) //create strcmp
	}


}

static int	find_and_replace(char **str, t_environ *env)
{
	char	*tmp;
	char	*dollar;
	char	*limit;

	if (!str || !*str)
		return (1);
	tmp = *str;
	while (tmp)
	{
		dollar = ft_strchr(tmp, '$');
		if (!dollar)
			return (0);
		limit = find_limit(dollar + 1); //if there is nothing ater dollar, it will be printed
		if (limit == dollar + 1)
			tmp = limit;
		else
			tmp = split_expand_join(str, dollar, limit, env);
	}
	if (!tmp)
		return (1);
	return (0);
}

/*expands environment variable to their values;
environment variable names consist solely of
uppercase letters, digits, and the <underscore>
and do not begin with a digit. */
int	expand_env(t_lexer *tokens, t_environ *env)
{
	int	i;

	i = 0;
	while (tokens)
	{
		if (tokens->type == HEREDOC) //to not expand what comes after a heredoc
		{
			while (tokens->next && tokens->next->space_after == 0) //check if it segfaults when << is the laste element of the line
					tokens = tokens->next;
		}
		if (tokens->type == WORD && !(tokens->quote == SINGLE))
		{
			if (i = 1 || !tokens->str)
				return (error_int(EXPAN_ERR));
			if (ft_strchr(tokens->str, '$'))
				i = find_and_replace(&(tokens->str), env);
		}
		tokens = tokens->next;
	}
	return (0);
}
/*
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ echo > $A
bash: $A: ambiguous redirect
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ echo $A

//wird nicht als syntax error gesehen
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ echo > $A | ls
bash: $A: ambiguous redirect
 incl   libft   Makefile   srcs
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ echo > "$A" | ls
bash: : No such file or directory
 incl   libft   Makefile   srcs
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ echo > '$A' | ls
 '$A'   incl   libft   Makefile   srcs

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ $A
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ '$A'
$A: command not found
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ "$A"
Command '' not found, but can be installed with:

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ls "$A"
ls: cannot access '': No such file or directory
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ls $A
'$USER'   incl   libft   Makefile   pbencze   srcs
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ls '$A'
ls: cannot access '$A': No such file or directory

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ pwd > file1  > $A | ls
bash: $A: ambiguous redirect
file1  incl  libft  Makefile  srcs

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ls "$A"
ls: cannot access '': No such file or directory
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ls "$A"-l
total 8
-rw-r--r-- 1 pbencze 2023_berlin    0 May  1 17:15 file1
drwxr-xr-x 2 pbencze 2023_berlin   60 May  1 16:21 incl
drwxr-xr-x 2 pbencze 2023_berlin 4096 Apr 30 16:38 libft
-rw-r--r-- 1 pbencze 2023_berlin 1344 May  1 16:21 Makefile
drwxr-xr-x 6 pbencze 2023_berlin  138 May  1 16:21 srcs
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ cat << hi
> $USER
> hi
pbencze
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ cat << hi"hey"
> $USER
> hihey
$USERec

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ << ''
>

pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ << hi | abab | << h ><
bash: syntax error near unexpected token `<'
> hi
> h
pbencze@c3a8c2:~/Documents/42cursus/Minishell/Minishell_Github$ ><< hi | abab | << h
bash: syntax error near unexpected token `<<'

2. expansion (if heredoc: jump until space after -> start expansion)
3. join words
4. heredocs
// files werden nicht erstellt beim syntax error, aber heredocs bis zum error schon, also den letzten token mit error flaggen und bis dahin heredocs machen
*/

