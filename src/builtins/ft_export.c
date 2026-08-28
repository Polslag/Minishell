/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:50 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/28 17:59:43 by pilagach         ###   ########.fr       */
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
	// if ()
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

// int	export_solo(t_env **envi)
// {

// }

char	*ft_get_key(char *s)
{
	char	*ret;
	char	*sep_ptr;
	int		j;
	int		sep;

	j = 0;
	sep_ptr = ft_strchr(s, '=');
	if (!sep_ptr)
		return (s);
	sep = sep_ptr - s;
	ret = malloc(sizeof(char) * (sep + 1));
	if (!ret)
		return (NULL);
	while (j < sep)
	{
		ret[j] = s[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

void	ft_add_export(t_env **list, char **arg, int i)
{
	t_env	*new;
	t_env	*last;

	new = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	ft_inienv(&new);
	last = ft_lstlast(list);
	new->key = ft_get_key(arg[i]);
	printf("new key = %s\narg = %s\ndiff entre les deux = %d\n", new->key, arg[i], ft_strcmp(new->key, arg[i]));
	if (!ft_strcmp(new->key, arg[i]))
		new->value = NULL;
	else
		new->value = ft_split_value(arg, i);
	printf("value = %s\n", new->value);
	new->next = NULL;
	last->next = new;
	last = last->next;
	printf("%s=%s\n", last->key, last->value);
	return ;
}

int	ft_export(char **arg, t_env **envi)
{
	int		i;
	int		error;
	char	*key;

	i = 1;
	error = 0;
	// if (!arg[i])
	// 	return (export_solo(envi));
	while (arg[i])
	{
		key = ft_get_key(arg[i]);
		printf("key = %s\n", key);
		if (!ft_check_key(key))
		{
			if (!ft_already_key(key, envi))
				ft_change_key(arg[i], key, envi);
			else
				ft_add_export(envi, arg, i);
		}
		else
			error = 1;
		t_env *last = ft_lstlast(envi);
		printf("\n\n\n");
		printf("%s=%s\n", last->key, last->value);
		free(key);
		i++;
	}
	return (error);
}
