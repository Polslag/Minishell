/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 13:13:39 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:14:27 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_poschr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

char	*ft_split_key(char **env, int i)
{
	char	*ret;
	int		j;
	int		sep;

	j = 0;
	sep = ft_find_poschr(env[i], '=');
	if (sep < 0)
		return (NULL);
	ret = malloc(sizeof(char) * (sep + 1));
	if (!ret)
		return (NULL);
	while (j < sep)
	{
		ret[j] = env[i][j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_split_value(char **env, int i)
{
	char	*ret;
	int		len_max;
	int		j;
	int		sep;

	j = 0;
	len_max = ft_strlen(env[i]);
	sep = ft_find_poschr(env[i], '=') + 1;
	if (sep < 0)
		return (NULL);
	ret = malloc(sizeof(char) * (len_max - sep + 1));
	if (!ret)
		return (NULL);
	while (env[i][j + sep])
	{
		ret[j] = env[i][j + sep];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
