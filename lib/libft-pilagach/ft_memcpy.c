/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:39:59 by pilagach          #+#    #+#             */
/*   Updated: 2025/11/25 14:50:26 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*strd;
	const unsigned char	*strsc;

	i = 0;
	strd = (unsigned char *)dest;
	strsc = (const unsigned char *)src;
	if (strd == NULL && strsc == NULL)
		return (NULL);
	while (i < n)
	{
		strd[i] = strsc[i];
		i++;
	}
	return (strd);
}
