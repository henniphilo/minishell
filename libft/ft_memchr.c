/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:31:40 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/16 16:56:28 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  The  memchr()  function  scans  the  initial n bytes of the memory area
       pointed to by s for the first instance of c.  Both c and the  bytes  of
       the memory area pointed to by s are interpreted as unsigned char.*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (size--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
