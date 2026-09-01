/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:38:47 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/01 14:19:26 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		ft_free_data(data);
		free(data);
		return (NULL);
	}
	data->cmd = NULL;
	data->last_return = 0;
	data->envi = ft_envsetup(ft_tablen(env), env);
	return (data);
}

void	syntax_error(t_data *data)
{
	ft_putstr_fd("minishell: syntax error\n", 2);
	data->last_return = 2;
}
