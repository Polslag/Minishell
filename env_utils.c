/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:14:33 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 14:16:41 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_envlen(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
void    ft_strcat(char *dst, char *src)
{
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return ;
}

char	**convert_env_to_array(t_env *env)
{
	t_env	*node;
	char	**array;
	int		i;

	i = 0;
	node = env;
	array = malloc(sizeof(char *) * (get_envlen(env) + 1));
	if (!array)
		return (NULL);
	while (node)
	{
		array[i] = (char *)ft_calloc(sizeof(char), (ft_strlen(node->key) + ft_strlen(node->value) + 2));
		ft_strcat(array[i], node->key);
		ft_strcat(array[i], "=");
		ft_strcat(array[i], node->value);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}