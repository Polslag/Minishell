/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:47 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:21:26 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isoperand(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	ft_is_only_num(char *str)
{
	int	i;

	i = 0;
	if (ft_isoperand(str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_abc(t_data *data)
{
	write(data->cmd->fd_out, "exit: ", ft_strlen("exit: "));
	write(data->cmd->fd_out, data->cmd->argv[1], ft_strlen(data->cmd->argv[1]));
	write(data->cmd->fd_out, ": numeric argument required\n", 28);
	ft_freeenv(&(data->envi));
	// ft_free_data(data);
	exit(2);
}

int	ft_exit(t_data *data)
{
	int	value;

	if (data->cmd->argv[1] && data->cmd->argv[2])
	{
		write(data->cmd->fd_out, "exit: too many arguments\n", 25);
		return (1);
	}
	if (data->cmd->argv[1])
	{
		if (ft_is_only_num(data->cmd->argv[1]))
		{
			value = ft_atoi(data->cmd->argv[1]);
			ft_freeenv(&(data->envi));
			// ft_free_data(data);
			exit(value);
		}
		else
			ft_exit_abc(data);
	}
	else
	{
		ft_freeenv(&(data->envi));
		// ft_free_data(data);
		exit(0);
	}
	return (1);
}
