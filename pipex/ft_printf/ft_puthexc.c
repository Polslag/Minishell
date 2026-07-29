/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:57:46 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 14:57:47 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexc(unsigned int hex, char *base)
{
	int	count;

	count = 0;
	if (ft_checkbase(base))
	{
		if (hex >= 16)
			count += ft_puthexc(hex / 16, base);
		ft_putchar(base[hex % 16]);
		count++;
	}
	return (count);
}
