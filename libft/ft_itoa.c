/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:50:53 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/22 18:43:25 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.*/

#include "libft.h"

static int	num_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*handle_min_int(void)
{
	char	*min_str;

	min_str = ft_strdup("-2147483648");
	if (!min_str)
		return (NULL);
	return (min_str);
}

char	*ft_itoa(int n)
{
	int		nlen;
	char	*str;
	int		sign;

	if (n == INT_MIN)
		return (handle_min_int());
	nlen = num_len(n);
	str = (char *)malloc((nlen + 1) * sizeof(char));
	if (n == 0)
		str[0] = '0';
	if (!str)
		return (NULL);
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		str[0] = '-';
	}
	str[nlen] = '\0';
	while (n != 0)
	{
		str[--nlen] = '0' + (n % 10) * sign;
		n = n / 10;
	}
	return (str);
}
