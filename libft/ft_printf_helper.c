/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:33:27 by hwiemann          #+#    #+#             */
/*   Updated: 2023/06/09 16:43:37 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wrt_char(int c)
{
	write(1, &c, 1);
	return (1);
}

size_t	ft_wrt_str(char *s)
{
	size_t	i;

	if (s == NULL)
	{
		write(1, NULL_DISPLAY, ft_strlen(NULL_DISPLAY));
		return (6);
	}
	i = 0;
	while (*s)
	{
		write(1, s++, 1);
		i++;
	}
	return (i);
}

size_t	ft_wrt_base_ptr(void *ptr, char *base, int first_flag)
{
	unsigned long long	nbr;
	size_t				base_len;
	size_t				i;

	nbr = (unsigned long long)ptr;
	base_len = ft_strlen(base);
	i = 0;
	if (ptr == NULL)
	{
		i += ft_wrt_str(NIL_DISPLAY);
		return (i);
	}
	if (first_flag == 1)
		i += ft_wrt_str(POINTER_PREFIX);
	if (nbr >= base_len)
		i += ft_wrt_base_ptr((void *)(nbr / base_len), base, 0);
	i += ft_wrt_char(base[nbr % base_len]);
	return (i);
}

size_t	ft_wrt_base_nbr(int nbr, char *base)
{
	int		base_len;
	long	lnbr;
	size_t	i;

	base_len = ft_strlen(base);
	lnbr = nbr;
	i = 0;
	if (lnbr < 0)
	{
		i += ft_wrt_char('-');
		lnbr *= -1;
	}
	if (lnbr >= base_len)
		i += ft_wrt_base_nbr(lnbr / base_len, base);
	i += ft_wrt_char(base[lnbr % base_len]);
	return (i);
}

size_t	ft_wrt_base_unsnbr(unsigned int nbr, char *base)
{
	unsigned int		base_len;
	unsigned long long	lnbr;
	size_t				i;

	base_len = ft_strlen(base);
	lnbr = nbr;
	i = 0;
	if (lnbr >= base_len)
		i += ft_wrt_base_nbr(lnbr / base_len, base);
	i += ft_wrt_char(base[lnbr % base_len]);
	return (i);
}
