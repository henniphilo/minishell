/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:59:40 by hwiemann          #+#    #+#             */
/*   Updated: 2024/05/03 15:26:36 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strdup() function returns a pointer to a new string which is a
duplicate of the string s.  Memory for the new string  is  obtained  with
malloc(3), and can be freed with free(3) */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
