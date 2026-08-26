/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:38 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:21:33 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_env *envi)
{
	int		i;
	char	*home;

	home = "HOME";
	while (envi->next != NULL)
	{
		i = 0;
		while (envi->key[i] == home[i] && home[i])
			i++;
		if (!home[i])
			return (envi->value);
		envi = envi->next;
	}
	i = 0;
	while (envi->key[i] == home[i] && home[i])
		i++;
	if (!home[i])
		return (envi->value);
	return (NULL);
}

char	*ft_establish_path(char *s)
{
	char	*pwd;
	char	*ret;

	if (s[0] == '/')
		return (s);
	ret = getcwd(NULL, 0);
	pwd = ft_strjoin(ret, "/");
	free(ret);
	ret = ft_strjoin(pwd, s);
	free(pwd);
	return (ret);
}

void	newpwd(t_env **envi)
{
	t_env	*node;

	node = (*envi);
	while (node)
	{
		if (!ft_strcmp(node->key, "PWD"))
		{
			free(node->value);
			node->value = getcwd(NULL, 0);
			return ;
		}
		node = node->next;
	}
}

void	pwdold(char *oldpwd, t_env **envi)
{
	t_env	*node;

	node = (*envi);
	while (node)
	{
		if (!ft_strcmp(node->key, "OLDPWD"))
		{
			free(node->value);
			node->value = oldpwd;
			return ;
		}
		node = node->next;
	}
}

int	ft_cd(char *s, t_env **envi)
{
	char	*path;
	char	*oldpwd;
	t_env	*e;

	e = (*envi);
	oldpwd = NULL;
	oldpwd = getcwd(NULL, 0);
	if (!s)
		path = get_home(e);
	else
		path = ft_establish_path(s);
	if (!path)
		return (1);
	if (chdir(path) < 0)
		return (1);
	newpwd(envi);
	pwdold(oldpwd, envi);
	free(path);
	return (0);
}
