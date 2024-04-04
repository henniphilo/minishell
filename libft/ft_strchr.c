/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:22:26 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/19 17:28:05 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* first occurance of c in string */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char) c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((unsigned char)*s == (unsigned char) c)
	{
		return ((char *) s);
	}
	return (NULL);
}

/*
char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return (&((char*)s)[i]);
}
*/
