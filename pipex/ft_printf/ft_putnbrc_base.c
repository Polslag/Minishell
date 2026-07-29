/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrc_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:21:11 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 14:21:15 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrc_base(int n, char *base)
{
	int				count;
	unsigned int	b_len;
	unsigned int	nbr;

	count = 0;
	b_len = (unsigned int)ft_strlen(base);
	if (ft_checkbase(base))
	{
		if (n < 0)
		{
			ft_putchar('-');
			count++;
			nbr = -n;
		}
		else
			nbr = n;
		if (nbr >= b_len)
			count += ft_putnbrc_base(nbr / b_len, base);
		ft_putchar(base[nbr % b_len]);
		count++;
	}
	return (count);
}
