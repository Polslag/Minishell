/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 13:16:26 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/24 13:16:51 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freeenv(t_env **envi)
{
	t_env	*bob;

	while ((*envi))
	{
		bob = (*envi)->next;
		free((*envi)->key);
		free((*envi)->value);
		free((*envi));
		(*envi) = bob;
	}
	free((*envi));
}
