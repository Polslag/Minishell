/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 13:14:53 by pilagach          #+#    #+#             */
/*   Updated: 2026/09/01 15:51:23 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_inienv(t_env **list)
{
	(*list)->key = NULL;
	(*list)->value = NULL;
	(*list)->next = NULL;
}

t_env	*ft_lstlast(t_env **list)
{
	t_env	*node;

	node = (*list);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ft_addenv(t_env **list, char **env, int i)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_inienv(&new);
	new->key = ft_split_key(env, i);
	new->value = ft_split_value(env, i);
	if (!new->key || !new->value)
	{
		free(new->value);
		free(new->key);
		free(new);
		return ;
	}
	if (!(*list))
		*list = new;
	else
		ft_lstlast(list)->next = new;
}

t_env	*ft_envsetup(int env_len, char **env)
{
	t_env	*envi;
	int		i;

	if (!env_len | !env)
	{
		return(NULL);
	}
	envi = NULL;
	i = 0;
	while (i < env_len)
	{
		ft_addenv(&envi, env, i);
		i++;
	}
	return (envi);
}
