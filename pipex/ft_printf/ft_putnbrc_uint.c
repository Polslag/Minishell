/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrc_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:51:38 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 14:51:39 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrc_uint(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
		count += ft_putnbrc_uint(n / 10);
	ft_putchar((n % 10) + '0');
	count++;
	return (count);
}
