/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:50:15 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/30 23:15:47 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_exec_file(char *p)
{
	struct stat	st;

	return (stat(p, &st) == 0 && S_ISREG(st.st_mode)
		&& access(p, X_OK) == 0);
}

int	find_path_env(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (ev[i][0] == 'P' && ev[i][1] == 'A' && ev[i][2] == 'T'
			&& ev[i][3] == 'H' && ev[i][4] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**obtain_path(char **ev)
{
	char	*path;
	char	**tab;
	int		i;
	int		j;

	i = find_path_env(ev);
	if (i == -1)
	{
		return (NULL);
	}
	path = malloc(sizeof(char) * (ft_strlen(ev[i]) - 4));
	if (!path)
		return (NULL);
	j = 0;
	while (ev[i][j + 5])
	{
		path[j] = ev[i][j + 5];
		j++;
	}
	path[j] = '\0';
	tab = ft_split(path, ':');
	free(path);
	return (tab);
}

static char	*command_path_search(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmdslash;

	cmdslash = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmdslash);
		if (is_exec_file(cmd_path))
		{
			free(cmdslash);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(cmdslash);
	return (NULL);
}

char	*command_path(char *cmd, char **path)
{
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (path == NULL)
		return (NULL);
	return (command_path_search(cmd, path));
}
