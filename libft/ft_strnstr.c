/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:57:00 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/19 16:48:55 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The strnstr() function locates the first occurrence of the null-termi‐
     nated string little in the string big, where not more than len characters
     are searched. If little is an empty string, big is returned; if little 
	 occurs nowhere in big, NULL is returned; otherwise a pointer to the first 
	 character of the first occurrence of little is returned. */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (*needle == '\0' || needle == NULL)
		return ((char *)hay);
	while (hay[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] == hay[i + j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *)hay + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
