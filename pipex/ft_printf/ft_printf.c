/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:42:53 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/02 20:12:23 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checkflag(va_list *ap, char flag)
{
	const t_fn	library[9] = {
	{.flag = 'c', .function = &c_caller},
	{.flag = 's', .function = &s_caller},
	{.flag = 'p', .function = &p_caller},
	{.flag = 'd', .function = &d_caller},
	{.flag = 'i', .function = &i_caller},
	{.flag = 'u', .function = &u_caller},
	{.flag = 'x', .function = &xlow_caller},
	{.flag = 'X', .function = &xup_caller},
	};
	int			i;

	i = 0;
	if (flag == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	while (flag != library[i].flag && library[i].flag)
		i++;
	if (library[i].flag != '\0')
		return (library[i].function(ap));
	return (0);
}

int	ft_printf(const char *input, ...)
{
	va_list	argptr;
	int		count;

	va_start(argptr, input);
	count = 0;
	while (*input)
	{
		if (*input == '%')
		{
			count += ft_checkflag(&argptr, *(++input));
		}
		else
		{
			ft_putchar(*input);
			count++;
		}
		input++;
	}
	va_end(argptr);
	return (count);
}
