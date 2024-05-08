#include "../../incl/minishell.h"

/*frees one element of the command list used for parsing*/
void	delone_redirs(t_redir *redirs)
{
	if (redirs)
	{
		if (redirs->file)
			free(redirs->file);
		redirs->file = NULL;
		if (redirs->ambig_redir)
			free(redirs->ambig_redir);
		redirs->ambig_redir = NULL;
		free(redirs);
	}
}

/*frees the command list used for parsing*/
void	free_redirs(t_redir **redirs)
{
	if (redirs && *redirs)
	{
		free_redirs(&(*redirs)->next);
		delone_redirs(*redirs);
		*redirs = NULL;
	}
}
