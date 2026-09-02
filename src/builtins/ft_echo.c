/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:44 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/30 22:36:41 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dash_n(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (0);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

static int	echo_put(int fd, char *s, int *err)
{
	if (*err)
		return (1);
	if (write(fd, s, ft_strlen(s)) < 0)
	{
		ft_putstr_fd("minishell: echo: write error: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		*err = 1;
	}
	return (*err);
}

int	ft_echo(t_command *cmd)
{
	int	i;
	int	nl_flag;
	int	err;

	i = 1;
	nl_flag = 1;
	err = 0;
	while (cmd->argv[i] && is_dash_n(cmd->argv[i]))
	{
		nl_flag = 0;
		i++;
	}
	while (cmd->argv[i] && cmd->argv[i + 1])
	{
		echo_put(cmd->fd_out, cmd->argv[i], &err);
		echo_put(cmd->fd_out, " ", &err);
		i++;
	}
	if (cmd->argv[i])
		echo_put(cmd->fd_out, cmd->argv[i], &err);
	if (nl_flag)
		echo_put(cmd->fd_out, "\n", &err);
	return (err);
}
