/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:32:20 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/17 13:09:21 by hwiemann         ###   ########.fr       */
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

/* int main() 
{
    char src[] = "Hello, World!";
    char dst[20];
    size_t size = strlen(src) + 1; // Including the null terminator

    printf("Source string: %s\n", src);
    printf("Size of the string: %zu\n", size);

    ft_memmove(dst, src, size);

    printf("After ft_memmove, dest string: %s\n", dst);

    return 0;
} */
