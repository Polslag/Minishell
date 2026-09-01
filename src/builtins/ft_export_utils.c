/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 21:30:00 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 22:36:47 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	ft_addenv_key(t_env **list, char *key)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_inienv(&new);
	new->key = ft_strdup(key);
	new->value = NULL;
	if (!(*list))
	{
		(*list) = new;
		return ;
	}
	ft_lstlast(list)->next = new;
}

static char	*ft_export_min_after(t_env *envi, char *prev)
{
	char	*min;

	min = NULL;
	while (envi)
	{
		if ((!prev || ft_strcmp(envi->key, prev) > 0)
			&& (!min || ft_strcmp(envi->key, min) < 0))
			min = envi->key;
		envi = envi->next;
	}
	return (min);
}

static void	ft_export_print(t_env *envi, char *key)
{
	while (envi && ft_strcmp(envi->key, key))
		envi = envi->next;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(key, 1);
	if (envi->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(envi->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

int	ft_export_list(t_env *envi)
{
	char	*key;

	key = ft_export_min_after(envi, NULL);
	while (key)
	{
		ft_export_print(envi, key);
		key = ft_export_min_after(envi, key);
	}
	return (0);
}
