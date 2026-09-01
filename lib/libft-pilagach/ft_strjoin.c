/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:22:12 by pilagach          #+#    #+#             */
/*   Updated: 2026/09/01 14:16:41 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stddef.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	str_len;
	size_t	s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	str_len = s1_len + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	while (i < str_len)
	{
		if (i < s1_len)
			str[i] = s1[i];
		else
			str[i] = s2[i - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}
