/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:44 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/23 17:28:51 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i] && cmd->argv[i + 1])
	{
		write(cmd->fd_out, cmd->argv[i], ft_strlen(cmd->argv[i]));
		i++;
	}
	if (ft_strcmp(cmd->argv[i], "-n"))
	{
		write(cmd->fd_out, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(1, "\n", 1);
	}
	return (0);
}
