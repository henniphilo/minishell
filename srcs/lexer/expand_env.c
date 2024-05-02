#include "../../incl/minishell.h"


static char *find_limit(char *dollar)
{
	while (*dollar)
	{
		if (!(*dollar >))
		dollar++;
	}
}

int	find_and_replace(char **str)
{
	char	*tmp;
	char	*dollar;
	char	*limit;
	char	*name;
	char	*value;

	tmp = NULL;
	if (!str)
		return (-1);
	dollar = ft_strchr(str, '$');
	limit = find_limit(dollar);
	name = ft_substr(dollar, 1, limit - dollar);
	if (!name)
		return (-1);
	tmp = split_expand_join(str, dollar, limit);
	free(*str);
	str = tmp;
	return(ft_strlen((const char *)value));
	return (0);
}

int	expand_env(t_lexer *tokens)
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
			if (i = -1 || !tokens->str)
				return (NULL);
			while (ft_strchr(&(tokens->str[i]), '$'))
				i = find_and_replace(&(tokens->str));
		}
		tokens = tokens->next;
	}
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

