/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:59:08 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/24 11:59:50 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

/* static void	print_tokens(t_lexer *tokens)
{
	while (tokens)
	{
		printf("string: %s\ntype: %i\nquote:
		 %i\nambig_redir: %s\n\n", tokens->str,
		 tokens->type, tokens->quote, tokens->ambig_redir);
		tokens = tokens->next;
	}
}
static void	print_cmds(t_command *cmds)
{
	int		i;
	t_redir	*redirs;

	while (cmds)
	{
		printf("\n");
		printf("command: %s\n", cmds->cmd);
		printf("fd_in: %i\n", cmds->fd_in);
		printf("fd_out: %i\n", cmds->fd_out);
		i = 0;
		if (cmds->args)
		{
			while (cmds->args[i])
			{
				printf("args[%i]: ", i);
				printf("%s\n", cmds->args[i]);
				i++;
			}
		}
		else
			(printf("args: %p\n", cmds->args));
		i = 0;
		if (cmds->argv)
		{
			while (cmds->argv[i])
			{
				printf("argv[%i]: ", i);
				printf("%s\n", cmds->argv[i]);
				i++;
			}
		}
		else
			(printf("argv: %p\n", cmds->argv));
		printf("redirs: \n");
		redirs = cmds->redirs;
		cmds = cmds->next;
	}
} */

void	test(t_data *shell)
{
	printf("\nLEXER:\n");
	print_tokens(shell->tokens);
	printf("\nPARSER:\n");
	print_cmds(shell->toex);
	printf("\nnumber of pipes: %i\n\n", count_commands(shell->tokens));
}
