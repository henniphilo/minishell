#include "../../incl/minishell.h"

static int	open_file(t_command *toex, t_redir *redirs)
{
	if ((redirs->type == INPUT) || (redirs->type == HEREDOC))
	{
		close(toex->fd_in);
		toex->fd_in = open(redirs->file, O_RDONLY, 0777);
		if (toex->fd_in == -1)
			return (file_err_int(redirs->file));
	}
	if (redirs->type == OUTPUT)
	{
		close(toex->fd_out);
		toex->fd_out = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (toex->fd_out == -1)
			return (file_err_int(redirs->file));
	}
	if (redirs->type == APPEND)
	{
		close(toex->fd_out);
		toex->fd_out = open(redirs->file, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (toex->fd_out == -1)
			return (file_err_int(redirs->file));
	}
	return (0);
}

int	handle_redirs(t_command *toex)
{
	t_redir	*redirs;

	redirs = NULL;
	while (toex)
	{
		redirs = toex->redirs;
		while (redirs)
		{
			if (redirs->ambig_redir)
				return (ambig_redir_err_int(redirs->ambig_redir));
			if (open_file(toex, redirs))
				return (1);
			redirs = redirs->next;
		}
		toex = toex->next;
	}
	return (0);
}
