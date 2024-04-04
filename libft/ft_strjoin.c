/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:51:10 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/17 11:24:05 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.*/

#include "libft.h"

static char	*ft_strcat(char *s1, const char *s2)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i])
		s1[len++] = s2[i++];
	s1[len] = '\0';
	return (s1);
}

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	size = 0;
	if (s1)
		size += ft_strlen (s1);
	if (s2)
		size += ft_strlen (s2);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (NULL);
	if (s1 && s2)
	{
		ft_strcat(ft_strcpy(result, s1), s2);
		return (result);
	}
	else if (s1 != NULL && s2 == NULL)
		return (ft_strcpy(result, s1));
	else if (s1 == NULL && s2 != NULL)
		return (ft_strcpy(result, s2));
	else
		return (NULL);
}
