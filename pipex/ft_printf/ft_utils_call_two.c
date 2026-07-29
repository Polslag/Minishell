/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_call_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:28:02 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 13:28:04 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_caller(va_list *ap)
{
	return (ft_putnbrc_uint(va_arg(*ap, unsigned int)));
}

int	xlow_caller(va_list *ap)
{
	return (ft_puthexc(va_arg(*ap, unsigned int), "0123456789abcdef"));
}

int	xup_caller(va_list *ap)
{
	return (ft_puthexc(va_arg(*ap, unsigned int), "0123456789ABCDEF"));
}
