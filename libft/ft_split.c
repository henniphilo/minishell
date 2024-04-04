/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:34:47 by hwiemann          #+#    #+#             */
/*   Updated: 2024/02/13 12:48:08 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.*/

#include "libft.h"

static int	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**newarr;
	size_t	word_len;
	int		i;

	newarr = (char **)malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!s || !newarr)
		return (NULL);
	i = 0;
	while (*s)
	{
		ft_printf("in split\n");
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				word_len = ft_strlen(s);
			else
				word_len = ft_strchr(s, c) - s;
			newarr[i++] = ft_substr(s, 0, word_len);
			s += word_len;
		}
	}
	newarr[i] = NULL;
	return (newarr);
}
/* in 51+52 alle Trennzeichen am Anfang des strings werden uebersprungen
            und uebrprueft ob string noch nicht yu ende ist*/
/* ab 58 teilstring erstellen von Position 0 bis zur laenge
            teilstring wird bei array an position i gespeichert
            und pointer auf ende des aktuellen worts verschoben*/
