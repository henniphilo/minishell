/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:30:06 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/17 13:03:25 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  bzero() function erases the data in the n bytes of the memory
       starting at the location pointed to by s, by writing zeros  (bytes
       containing '\0') to that area.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
