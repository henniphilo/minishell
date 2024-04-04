/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:32:39 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/17 11:28:27 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	slen;
	unsigned int	dlen;

	i = 0;
	slen = 0;
	while (src[slen])
		slen++;
	dlen = 0;
	while (dst[dlen] && dlen < size)
		dlen++;
	if (size <= dlen)
		return (slen + size);
	while (src[i] && dlen + 1 + i < size)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
