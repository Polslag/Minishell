/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 23:57:02 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/02 11:38:10 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_set_or_add(t_env **envi, char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(value);
		return ;
	}
	ft_inienv(&node);
	node->key = ft_strdup(key);
	node->value = value;
	if (!(*envi))
		*envi = node;
	else
		ft_lstlast(envi)->next = node;
}

char	*ft_cd_move(char *s, t_env **envi, char *oldpwd)
{
	char	*path;

	if (!s)
		path = cd_home(*envi);
	else
		path = ft_strdup(s);
	if (!path)
	{
		free(oldpwd);
		return (NULL);
	}
	if (chdir(path) < 0)
	{
		cd_error(path);
		free(path);
		free(oldpwd);
		return (NULL);
	}
	return (path);
}

int	ft_cd_check(t_command *cmd, t_env *envi, char **s, int *is_dash)
{
	*s = cmd->argv[1];
	if (*s && cmd->argv[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (2);
	}
	if (*s && !(*s)[0])
	{
		ft_putstr_fd("minishell: cd: null directory\n", 2);
		return (1);
	}
	*is_dash = (*s && !ft_strcmp(*s, "-"));
	if (*is_dash)
		*s = ft_getenv_value(envi, "OLDPWD");
	if (*is_dash && !*s)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	return (0);
}
