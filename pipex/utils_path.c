/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:50:15 by pilagach          #+#    #+#             */
/*   Updated: 2026/03/27 16:39:34 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data)
{
	data->cmd = NULL;
	data->path = NULL;
	data->envp = NULL;
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
		ft_printf("Didn't find PATH in environment\n");
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

char	*command_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmdslash;

	i = 0;
	if (cmd == NULL || (cmd[0] != '/' && path == NULL))
		return (NULL);
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	cmdslash = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmdslash);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmdslash);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free(cmdslash);
	return (NULL);
}
