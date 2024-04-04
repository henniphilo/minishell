/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:16:54 by hwiemann          #+#    #+#             */
/*   Updated: 2023/06/07 15:03:34 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_process(char specifier, va_list ap)
{
	size_t	pos;

	pos = 0;
	if (specifier == 'c')
		pos = ft_wrt_char(va_arg(ap, int));
	else if (specifier == 's')
		pos = ft_wrt_str(va_arg(ap, char *));
	else if (specifier == 'p')
		pos = ft_wrt_base_ptr(va_arg(ap, void *), HEX_BASE_LOW, 1);
	else if (specifier == 'd' || specifier == 'i')
		pos = ft_wrt_base_nbr(va_arg(ap, int), DEC_BASE);
	else if (specifier == 'u')
		pos = ft_wrt_base_unsnbr(va_arg(ap, unsigned int), DEC_BASE);
	else if (specifier == 'x')
		pos = ft_wrt_base_unsnbr(va_arg(ap, unsigned int), HEX_BASE_LOW);
	else if (specifier == 'X')
		pos = ft_wrt_base_unsnbr(va_arg(ap, unsigned int), HEX_BASE_UP);
	else if (specifier == '%')
		pos = ft_wrt_char('%');
	return (pos);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	pos;

	va_start(args, format);
	pos = 0;
	while (*format)
	{
		if (*format == '%')
		{
			pos += ft_process(*++format, args);
			format++;
		}
		else
			pos += ft_wrt_char(*format++);
	}
	va_end(args);
	return (pos);
}
