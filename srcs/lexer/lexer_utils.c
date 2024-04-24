#include "../../incl/minishell.h"

/*function to handle syntax errors*/
int	check_pipe(char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '|')
		return (error_int(PIPE_ERR));
	return (0);
}

int	check_less(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '<')
		*type = HEREDOC;
	return (0);
}

int	check_more(t_type *type, char *buf) //missing: syntax error edge cases
{
	if (buf[1] == '>')
		*type = APPEND;
	return (0);
}
