#include "../../incl/minishell.h"

/*calculates the size of a 2D-array*/
int	array_len(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			i++;
	}
	return (i);
}

/*frees two 2D-arrays*/
char	**free_arr(char **arr1, char **arr2)
{
	int	i;

	i = 0;
	if (arr1)
	{
		while (arr1[i])
			free(arr1[i++]);
		free(arr1);
	}
	i = 0;
	if (arr2)
	{
		while (arr2[i])
			free(arr2[i++]);
		free(arr2);
	}
	return (NULL);
}

/*appends a string to a 2D-array*/
char	**append_arr(char **arr, char *new_str)
{
	int		i;
	char	**new_arr;

	if (!new_str)
		return (arr);
	i = array_len(arr);
	new_arr = (char **)ft_calloc((i + 2), sizeof(char *));
	if (!new_arr)
		return (free_arr(arr, NULL));
	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free_arr(arr, new_arr));
		i++;
	}
	new_arr[i] = ft_strdup(new_str);
	if (!new_arr[i])
		return (free_arr(arr, new_arr));
	free_arr(arr, NULL);
	return (new_arr);
}

int	count_commands(t_lexer *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
