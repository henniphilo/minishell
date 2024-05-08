#include "../../incl/minishell.h"

int	open_file(t_command *toex, t_redir *redirs)
{
	check_expansion();

	return (0);
}

int	handle_redirs(t_command *toex)
{
	t_redir *redirs;

	redirs = NULL;
	while (toex)
	{
		redirs = toex->redirs;
		while (redirs)
		{
			if (open_file(toex, redirs))
				return (1);
			redirs = redirs->next;
		}
		toex = toex->next;
	}
	return (0);
}
