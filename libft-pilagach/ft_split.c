/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:02:47 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/01 17:19:04 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_words(char const *s, char c)
{
	int	i;
	int	in_word;
	int	words;

	i = 0;
	words = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			words++;
		}
		i++;
	}
	return (words);
}

void	ft_strcpy(char *d, char *src, char c)
{
	int	i;

	i = 0;
	while (!(src [i] == c) && src[i])
	{
		d[i] = src[i];
		i++;
	}
	d[i] = '\0';
}

static char	**ft_free_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

int	alloc_n_write(char **strs, char *src, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (src[i])
	{
		if (src[i] == c)
			i++;
		else
		{
			j = 0;
			while (!(src[i + j] == c) && src[i + j])
				j++;
			strs[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!strs[k])
				return (0);
			ft_strcpy(strs[k], src + i, c);
			i += j;
			k++;
		}
	}
	strs[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		total;

	total = count_words(s, c);
	strs = (char **)malloc(sizeof(char *) * (total + 1));
	if (!strs)
		return (NULL);
	if (alloc_n_write(strs, (char *)s, c) == 0)
		return (ft_free_tab(strs));
	return (strs);
}	
