/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:07:21 by pilagach          #+#    #+#             */
/*   Updated: 2025/11/24 16:27:55 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = n;
	if (nbr == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', fd);
			nbr *= (-1);
			ft_putnbr_fd(nbr, fd);
		}
		else if (nbr > 9)
		{
			ft_putnbr_fd(nbr / 10, fd);
			ft_putchar_fd('0' + nbr % 10, fd);
		}
		else
			ft_putchar_fd('0' + nbr, fd);
	}
}
