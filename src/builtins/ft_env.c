/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:47 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/31 01:19:22 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **envi)
{
	t_env	*node;

	node = (*envi);
	while (node)
	{
		if (node->value != NULL)
		{
			ft_putstr_fd(node->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(node->value, 1);
		}
		node = node->next;
	}
	return (0);
}
