/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 17:22:18 by pilagach          #+#    #+#             */
/*   Updated: 2026/04/08 15:08:39 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd && data->cmd[++i])
		free(data->cmd[i]);
	if (data->cmd)
		free(data->cmd);
	data->cmd = NULL;
}

void	free_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->path && data->path[i])
	{
		free(data->path[i]);
		i++;
	}
	if (data->path)
		free(data->path);
	data->path = NULL;
}

void	freeer(t_data *data, char *cp)
{
	if (cp != NULL)
		free(cp);
	cp = NULL;
	free_cmd(data);
	free_path(data);
}

void	exiting(t_data *data, char *cp, int fdin, int fdout)
{
	freeer(data, cp);
	close_files(data, 2);
	if (fdin == -1 || fdout == -1)
		exit(1);
	exit(127);
}

int	close_files(t_data *data, int flag)
{
	int	temp;

	if (flag == 1)
		write(0, "Error\nFile not opened.\n", 23);
	close(data->fdin);
	temp = data->fdout;
	close(data->fdout);
	if (flag == 2)
	{
		close(data->pipe[0]);
		close(data->pipe[1]);
	}
	if (temp == -1)
		return (1);
	return (0);
}
