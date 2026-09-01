/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:50 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/30 22:36:50 by ysapelie         ###   ########.fr       */
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

	if (!key || !key[0])
		return (1);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	j = 1;
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

static int	ft_export_arg(char **arg, int i, t_env **envi)
{
	char	*key;
	int		error;

	error = 0;
	key = ft_export_key(arg[i]);
	if (ft_check_key(key))
		error = ft_export_error(arg[i]);
	else if (ft_strchr(arg[i], '='))
	{
		if (!ft_already_key(key, envi))
			ft_change_key(arg[i], key, envi);
		else
			ft_addenv(envi, arg, i);
	}
	else if (ft_already_key(key, envi))
		ft_addenv_key(envi, key);
	free(key);
	return (error);
}

int	ft_export(char **arg, t_env **envi)
{
	int	i;
	int	error;

	if (!arg[1])
		return (ft_export_list(*envi));
	i = 1;
	error = 0;
	while (arg[i])
	{
		if (ft_export_arg(arg, i, envi))
			error = 1;
		i++;
	}
	return (error);
}
