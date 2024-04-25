/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:47:45 by pbencze           #+#    #+#             */
/*   Updated: 2024/04/25 14:54:05 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/*puts an error message, frees data and exits the program*/
void	panic(char *str, void *ptr)
{
	if (str)
		ft_putendl_fd(str, 2);
	//optional: perror() or strerror() instead of putendl()
	if (ptr)
		free_data((t_data *)ptr);
	exit(1);
}

/*puts an error message and returns int 1*/
int	error_int(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}

/*puts an error message and returns NULL*/
void	*error_ptr(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	return (NULL);
}


