/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:38 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/30 23:15:39 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_home(t_env *envi)
{
	char	*home;

	home = ft_getenv_value(envi, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (ft_strdup(home));
}

void	newpwd(t_env **envi)
{
	t_env	*node;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return ;
	node = (*envi);
	while (node)
	{
		if (!ft_strcmp(node->key, "PWD"))
		{
			free(node->value);
			node->value = tmp;
			return ;
		}
		node = node->next;
	}
	env_set_or_add(envi, "PWD", tmp);
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
	env_set_or_add(envi, "OLDPWD", oldpwd);
}

int	ft_cd(t_command *cmd, t_env **envi)
{
	char	*path;
	char	*oldpwd;
	char	*s;
	int		is_dash;

	if (ft_cd_check(cmd, *envi, &s, &is_dash))
		return (1);
	oldpwd = getcwd(NULL, 0);
	path = ft_cd_move(s, envi, oldpwd);
	if (!path)
		return (1);
	if (is_dash)
		ft_putendl_fd(path, 1);
	newpwd(envi);
	pwdold(oldpwd, envi);
	free(path);
	return (0);
}
