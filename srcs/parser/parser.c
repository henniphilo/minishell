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
		// else // alles muss ins argv
		// {
		// 	printf("das ist gerade buffer : %s\n", shell->buf);
		// 	node->argv[0] = ft_strdup(shell->buf);
		// 	break ;
		// }
		node = node->next;
	}
	return (0);
}

int	parser(t_data *shell)
{
	shell->toex = create_cmdlist(shell->tokens);
	if (!shell->toex)
		return (error_int(PARSE_ERR));
	if (init_cmd_list(shell->tokens, shell) == 1)
		return (error_int(PARSE_ERR));
	if (init_argv(shell) == 1)
		return (error_int(PARSE_ERR));
	if (handle_redirs(shell->toex))
		return (1);
	return (0);
}
