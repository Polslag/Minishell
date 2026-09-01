/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 02:44:22 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 23:58:31 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_lookup(t_data *data, char *key)
{
	char	*value;

	if (!key)
		return (NULL);
	value = ft_getenv_value(data->envi, key);
	free(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
