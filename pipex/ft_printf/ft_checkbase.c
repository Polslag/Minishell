/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:31:05 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 14:31:06 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checkbase(char *base)
{
	int	i;
	int	j;
	int	b_len;

	i = 0;
	b_len = ft_strlen(base);
	if (b_len == 0 || b_len == 1)
		return (0);
	while (base[i])
	{
		if (base[i] < 32 || base[i] > 126)
			return (0);
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
