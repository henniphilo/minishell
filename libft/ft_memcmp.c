/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:31:50 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/19 16:23:54 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The  memcmp()  function  compares the first n bytes (each interpreted as un‐
    signed char) of the memory areas s1 and s2.
	The memcmp() function returns an integer less than,  equal  to,  or  greater
    than  zero  if  the  first  n bytes of s1 is found, respectively, to be less
    than, to match, or be greater than the first n bytes of s2.

    For a nonzero return value, the sign is determined by the sign of  the  dif‐
    ference  between the first pair of bytes (interpreted as unsigned char) that
    differ in s1 and s2.

    If n is zero, the return value is zero.*/

#include "libft.h"

int	ft_memcmp(const void *a1, const void *a2, size_t n)
{
	const unsigned char	*aa1;
	const unsigned char	*aa2;
	size_t				i;

	i = 0;
	aa1 = (const unsigned char *)a1;
	aa2 = (const unsigned char *)a2;
	while (i < n)
	{
		if (aa1[i] != aa2[i])
			return (aa1[i] - aa2[i]);
		i++;
	}
	return (0);
}
