/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:55:18 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/31 01:19:25 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**ft_search_key(t_env **envi, char *key)
{
	t_env	**cur;

	if (!key[0])
		return (NULL);
	cur = envi;
	while (*cur)
	{
		if (!ft_strcmp((*cur)->key, key))
			return (cur);
		cur = &(*cur)->next;
	}
	return (NULL);
}

int	ft_unset(t_env **envi, char **cmd)
{
	int		i;
	t_env	**slot;
	t_env	*tmp;

	i = 1;
	while (cmd[i])
	{
		slot = ft_search_key(envi, cmd[i]);
		if (slot)
		{
			tmp = (*slot)->next;
			free((*slot)->key);
			free((*slot)->value);
			free(*slot);
			*slot = tmp;
		}
		i++;
	}
	return (0);
}
