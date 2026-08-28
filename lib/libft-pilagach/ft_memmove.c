/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:24:07 by pilagach          #+#    #+#             */
/*   Updated: 2025/11/13 17:08:12 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	long	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if ((unsigned char *)dest < (const unsigned char *)src)
	{
		i = 0;
		while ((size_t)i < n)
		{
			*(unsigned char *)(dest + i) = *(const unsigned char *)(src + i);
			i++;
		}
		return (dest);
	}
	else
	{
		i = n - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dest + i) = *(const unsigned char *)(src + i);
			i--;
		}
		return (dest);
	}
}
