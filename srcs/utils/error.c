/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:47:45 by pbencze           #+#    #+#             */
/*   Updated: 2024/04/11 16:46:22 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	panic(char *str, void *ptr)
{
	if (str)
		ft_putendl_fd(str, 2);
	//optional: perror() or strerror() instead of putendl()
	if (ptr)
		free_data((t_data *)ptr);
	exit(1);
}
