/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 13:13:39 by pilagach          #+#    #+#             */
/*   Updated: 2026/09/01 15:45:21 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_export_key(char *s)
{
	char	*sep;

	sep = ft_strchr(s, '=');
	if (!sep)
		return (ft_strdup(s));
	return (ft_substr(s, 0, sep - s));
}

char	*ft_split_key(char **env, int i)
{
	char	*ret;
	char	*sep_ptr;
	int		j;
	int		sep;

	j = 0;
	sep_ptr = ft_strchr(env[i], '=');
	if (!sep_ptr)
		return (NULL);
	sep = sep_ptr - env[i];
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
	char	*sep_ptr;
	int		len_max;
	int		j;
	int		sep;

	j = 0;
	if (!env[i])
	{
		return(NULL);
	}	
	len_max = ft_strlen(env[i]);
	sep_ptr = ft_strchr(env[i], '=');
	if (!sep_ptr)
		return (NULL);
	sep = sep_ptr - env[i] + 1;
	ret = malloc(sizeof(char) * (len_max - sep + 1));
	if (!ret)
	{
		free(ret);
		return (NULL);
	}
	while (env[i][j + sep])
	{
		ret[j] = env[i][j + sep];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
