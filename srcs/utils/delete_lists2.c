/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_lists2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:04:27 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/24 16:25:21 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*frees one element of the token list used for lexing*/
void	delone_env_list(t_environ *env)
{
	if (env)
	{
		if (env->value)
			free(env->value);
		env->value = NULL;
		if (env->name)
			free(env->name);
		env->name = NULL;
		free(env);
		env = NULL;
	}
}

/*frees the token list used for lexing*/
void	free_env_list(t_environ **env)
{
	if (env && *env)
	{
		free_env_list(&(*env)->next);
		delone_env_list(*env);
		*env = NULL;
	}
}
