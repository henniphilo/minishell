/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:56:48 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/19 15:51:08 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The  strcmp()  function compares the two strings s1 and s2. 
strcmp() returns an integer indicating the result of the comparison*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && 0 < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
