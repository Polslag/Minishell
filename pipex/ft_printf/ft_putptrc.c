/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:57:28 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 13:57:29 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(size_t hex, char *base)
{
	int	count;

	count = 0;
	if (hex >= 16)
		count += ft_printptr(hex / 16, base);
	ft_putchar(base[hex % 16]);
	count++;
	return (count);
}

int	ft_putptrc(void *ptr)
{
	if (!ptr)
		return (ft_putstrc("(nil)"));
	write(1, "0x", 2);
	return (2 + ft_printptr((size_t)ptr, "0123456789abcdef"));
}
