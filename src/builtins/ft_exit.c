/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:47 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/30 23:15:43 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isoperand(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_is_only_num(char *str)
{
	int			i;
	long long	value;

	i = 0;
	if (ft_isoperand(str[i]))
		i++;
	if (!str[i])
		return (0);
	value = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		if (value > (9223372036854775807LL - (str[i] - '0')) / 10)
			return (0);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (1);
}

int	ft_exit_abc(t_command *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (2);
}

static void	ft_exit_arg(t_command *cmd, t_data *data)
{
	int	value;

	if (ft_is_only_num(cmd->argv[1]))
	{
		value = ft_atoi(cmd->argv[1]);
		ft_free_data(data);
		exit(value);
	}
}

int	ft_exit(t_command *cmd, t_data *data, int flag)
{
	if (flag)
	{
		write(1, "exit\n", 5);
		ft_free_data(data);
		exit(0);
	}
	write(2, "exit\n", 5);
	if (cmd->argv[1] && cmd->argv[2])
	{
		ft_error_output(data, "exit:", "too many arguments\n", RD);
		return (2);
	}
	if (cmd->argv[1])
	{
		ft_exit_arg(cmd, data);
		return (ft_exit_abc(cmd));
	}
	ft_free_data(data);
	exit(0);
	return (1);
}
