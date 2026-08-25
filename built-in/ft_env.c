/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:54:47 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:21:26 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **envi)
{
	t_env	*node;

	node = (*envi);
	while (node)
	{
		printf("%s=", node->key);
		if (node->value == NULL)
			printf("\n");
		else
			printf("%s\n", node->value);
		node = node->next;
	}
	return (0);
}
