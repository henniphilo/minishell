/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:14:48 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/21 17:14:54 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	init_argv(t_data *shell)
{
	int			i;
	t_command	*node;

	node = shell->toex;
	while (node)
	{
		if (node->cmd)
		{
			node->argv = ft_calloc(array_len(node->args) + 2, sizeof(char *));
			if (!node->argv)
				return (error_int(ALLOC_ERR));
			node->argv[0] = ft_strdup(node->cmd);
			if (!node->argv[0])
				return (error_int(ALLOC_ERR));
			i = -1;
			while (node->args && node->args[++i])
			{
				node->argv[i + 1] = ft_strdup(node->args[i]);
				if (!node->argv[i + 1])
					return (error_int(ALLOC_ERR));
			}
		}
		node = node->next;
	}
	return (0);
}

int	parser(t_data *shell)
{
	if (!shell->tokens)
		return (1);
	shell->toex = create_cmdlist(shell->tokens);
	if (!shell->toex)
		return (error_int(PARSE_ERR));
	if (init_cmd_list(shell->tokens, shell) == 1)
		return (error_int(PARSE_ERR));
	if (init_argv(shell) == 1)
		return (error_int(PARSE_ERR));
	if (handle_redirs(shell, shell->toex))
		return (0);
	return (0);
}
