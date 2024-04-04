/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwiemann <hwiemann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:33:41 by hwiemann          #+#    #+#             */
/*   Updated: 2023/05/22 19:12:03 by hwiemann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Outputs the integer ’n’ to the given file
descriptor.*/

#include "libft.h"

static void	ft_writenbr(int nb, int fd)
{
	if (!nb)
		return ;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		if (nb < -9)
			ft_writenbr(nb / 10 * -1, fd);
		ft_putchar_fd(nb % 10 * -1 + '0', fd);
	}
	else
	{
		if (nb > 9)
			ft_writenbr(nb / 10, fd);
		ft_putchar_fd (nb % 10 + '0', fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (!n)
		ft_putchar_fd('0', fd);
	else
		ft_writenbr(n, fd);
}
