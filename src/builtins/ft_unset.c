/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:55:18 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:21:00 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_search_key(t_env *envi, char *key)
{
	t_env	*node;

	node = envi;
	while (node)
	{
		if (node->next && !ft_strncmp(node->next->key, key, ft_strlen(key)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	ft_unset(t_env **envi, char **cmd)
{
	int		i;
	t_env	*node;
	t_env	*tmp;

	i = 1;
	while (cmd[i])
	{
		node = ft_search_key(*envi, cmd[i]);
		if (node)
		{
			tmp = node->next->next;
			free(node->next->key);
			free(node->next->value);
			free(node->next);
			node->next = tmp;
		}
		i++;
	}
	return (0);
}
