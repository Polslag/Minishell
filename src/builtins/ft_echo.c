/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:44 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/26 05:45:16 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 1;
	while (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
	{
		nl_flag = 0;
		i++;
	}
	while (cmd->argv[i] && cmd->argv[i + 1])
	{
		write(cmd->fd_out, cmd->argv[i], ft_strlen(cmd->argv[i]));
		write(cmd->fd_out, " ", 1);
		i++;
	}
	if (cmd->argv[i])
		write(cmd->fd_out, cmd->argv[i], ft_strlen(cmd->argv[i]));
	if (nl_flag)
		write(cmd->fd_out, "\n", 1);
	return (0);
}
