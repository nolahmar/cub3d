/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 12:35:55 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/11 09:29:54 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write (fd, "-", 1);
		write (fd, "2147483648", 10);
	}
	else if (nb < 0)
	{
		nb = nb * (-1);
		write (fd, "-", 1);
	}
	if (nb >= 0)
	{
		if (nb > 9)
		{
			ft_putnbr_fd (nb / 10, fd);
			ft_putnbr_fd (nb % 10, fd);
		}
		else
		{
			ft_putchar_fd(nb + '0', fd);
		}
	}
}
