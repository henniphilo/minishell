/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:02:56 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/22 10:14:09 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*frees the command list used for parsing*/
void	free_commands(t_command **cmds)
{
	if (cmds && *cmds)
	{
		free_commands(&(*cmds)->next);
		delone_commands(*cmds);
		*cmds = NULL;
	}
}

/*frees one element of the command list used for parsing*/
void	delone_commands(t_command *cmds)
{
	if (cmds)
	{
		if (cmds->cmd)
			free(cmds->cmd);
		free_arr(cmds->args, cmds->argv);
		free_redirs(&(cmds->redirs));
		if (cmds->fd_in > 0)
			close(cmds->fd_in);
		if (cmds->fd_out > 0)
			close(cmds->fd_out);
		free(cmds);
	}
}

/*frees one element of the token list used for lexing*/
void	delone_tokens(t_lexer *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		if (token->ambig_redir)
			free(token->ambig_redir);
		free(token);
	}
}

/*frees the token list used for lexing*/
void	free_tokens(t_lexer **tokens)
{
	if (tokens && *tokens)
	{
		free_tokens(&(*tokens)->next);
		delone_tokens(*tokens);
		*tokens = NULL;
	}
}
