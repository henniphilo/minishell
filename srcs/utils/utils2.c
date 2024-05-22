/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:12:10 by pbencze           #+#    #+#             */
/*   Updated: 2024/05/22 14:07:45 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (!ft_isdigit(str[i++]))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (2);
		}
	}
	return (0);
}

/*frees two strings and returns 1*/
int	free_strs(char *s1, char *s2)
{
	if (s1)
		free(s1);
	s1 = NULL;
	if (s2)
		free(s2);
	s2 = NULL;
	return (1);
}

int	check_doubles(char **args, int i)
{
	int	j;

	j = 0;
	while (i > 0 && j < i)
	{
		if (ft_strcmp(args[i], args[j]) == 0)
			return (1);
		j++;
	}
	return (0);
}
