/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:23:52 by pilagach          #+#    #+#             */
/*   Updated: 2025/11/24 16:12:14 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_nbr_len(long nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		len++;
	if (nb < 0)
	{
		nb *= (-1);
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(s);
	while (j > i)
	{
		j--;
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		i;
	int		neg;

	nb = n;
	neg = 0;
	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_nbr_len(nb) + 1));
	if (!str)
		return (NULL);
	if (nb < 0 && ++neg)
		nb *= (-1);
	if (nb == 0)
		str[i++] = '0';
	while (nb > 0)
	{
		str[i++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (neg == 1)
		str[i++] = '-';
	str[i] = '\0';
	return (ft_strrev(str));
}
