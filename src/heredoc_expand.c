/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 03:45:11 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/31 01:18:43 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_expand_unit(char *raw, int *i, t_data *data)
{
	char	buf[2];

	if (raw[*i] == '$')
		return (expand_dollar(raw, i, data));
	buf[0] = raw[(*i)++];
	buf[1] = '\0';
	return (ft_strdup(buf));
}

char	*heredoc_expand_line(char *raw, t_data *data)
{
	char	*result;
	char	*tmp;
	char	*val;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (result && raw[i])
	{
		val = heredoc_expand_unit(raw, &i, data);
		if (!val)
		{
			free(result);
			return (NULL);
		}
		tmp = ft_strjoin(result, val);
		free(result);
		free(val);
		result = tmp;
	}
	return (result);
}

char	*heredoc_maybe_expand(char *buff, int in_quote, t_data *data)
{
	char	*tmp;

	if (in_quote)
		return (buff);
	tmp = heredoc_expand_line(buff, data);
	free(buff);
	return (tmp);
}

char	*heredoc_append(char *str, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(str, buff);
	free(str);
	free(buff);
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, "\n");
	free(tmp);
	return (str);
}
