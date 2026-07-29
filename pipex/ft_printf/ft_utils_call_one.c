/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_call_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:15:42 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 13:15:44 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	c_caller(va_list *ap)
{
	ft_putchar(va_arg(*ap, int));
	return (1);
}

int	s_caller(va_list *ap)
{
	return (ft_putstrc(va_arg(*ap, char *)));
}

int	p_caller(va_list *ap)
{
	return (ft_putptrc(va_arg(*ap, void *)));
}

int	d_caller(va_list *ap)
{
	return (ft_putnbrc_base(va_arg(*ap, int), "0123456789"));
}

int	i_caller(va_list *ap)
{
	return (ft_putnbrc_base(va_arg(*ap, int), "0123456789"));
}
