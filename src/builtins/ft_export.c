/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:50 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:21:22 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_already_key(char *key, t_env **envi)
{
	t_env	*node;

	node = (*envi);
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (0);
		node = node->next;
	}
	return (1);
}

int	ft_check_key(char *key)
{
	int	j;

	j = 0;
	while (key[j])
	{
		if (!ft_isalnum(key[j]) && key[j] != '_')
			return (1);
		j++;
	}
	return (0);
}

void	ft_change_key(char *s, char *key, t_env **envi)
{
	char	*value;
	t_env	*node;

	node = (*envi);
	value = ft_split_value(&s, 0);
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			node->value = value;
			break ;
		}
		node = node->next;
	}
	return ;
}

int	ft_export(char **arg, t_env **envi)
{
	int		i;
	int		error;
	char	*key;

	i = 1;
	error = 0;
	while (arg[i])
	{
		key = ft_split_key(arg, i);
		if (!ft_check_key(key))
		{
			if (!ft_already_key(key, envi))
				ft_change_key(arg[i], key, envi);
			else
				ft_addenv(envi, arg, i);
		}
		else
			error = 1;
		free(key);
		i++;
	}
	return (error);
}
