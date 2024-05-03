#include "../../incl/minishell.h"

int	init_cmd_list(t_lexer *tokens, t_data *shell)
{
	t_command *node;

	node = shell->toex;
	while (tokens)
	{
		if (tokens->type == PIPE)
			node = node->next;
		else
		{
			if (!(tokens->type == WORD)) //later tbd: handling of redirections
				tokens = tokens->next; //later tbd: handling of redirections
			else
			{
				if (!node->cmd)
				{
					node->cmd = ft_strdup(tokens->str);
					if (!node->cmd)
						return (1);
				}
				else
				{
					node->args = append_arr(node->args, tokens->str); //temporary
					if (!node->args)
						return (1);
				}
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

/*creates a new node*/
t_command	*new_cmd_list(void)
{
	t_command	*new_node;

	new_node = ft_calloc(1, sizeof(t_command));
	if (!new_node)
		return (error_ptr(ALLOC_ERR));
	return (new_node);
}

/*returns the last element of the command list*/
t_command	*cmd_list_last(t_command *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*adds a node to the end of the command list*/
void	cmd_list_add_back(t_command **lst, t_command *new)
{
	t_command	*pos;

	if (lst)
	{
		pos = cmd_list_last(*lst);
		if (!pos)
			*lst = new;
		else
			pos->next = new;
	}
}

t_command	*create_cmdlist(t_lexer *tokens)
{
	t_command	*list;
	t_command	*node;
	int			i;

	list = NULL;
	node = NULL;
	i = 0;
	while (i < count_commands(tokens))
	{
		node = new_cmd_list();
		if (!node)
			return (NULL);
		cmd_list_add_back(&list, node);
		i++;
	}
	return (list);
}
