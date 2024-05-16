/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:32:20 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/16 14:36:46 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h>
#include <stdlib.h>
#include <string.h> */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	char	*s;
	char	*d;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (size-- > i)
			d[size] = s[size];
	}
	else
	{
		while (i < size)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
