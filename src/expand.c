/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 03:03:34 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 23:50:34 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*append_str(char *acc, char *s)
{
	char	*tmp;

	tmp = ft_strjoin(acc, s);
	free(acc);
	return (tmp);
}

char	*expand_dollar(char *raw, int *i, t_data *data)
{
	int		start;
	int		braced;
	char	*key;

	(*i)++;
	if (raw[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(data->last_return));
	}
	braced = (raw[*i] == '{');
	if (braced)
		(*i)++;
	start = *i;
	while (raw[*i] && ((braced && raw[*i] != '}')
			|| (!braced && is_var_char(raw[*i]))))
		(*i)++;
	if (*i == start && !braced)
		return (ft_strdup("$"));
	key = ft_substr(raw, start, *i - start);
	if (braced && raw[*i] == '}')
		(*i)++;
	return (expand_lookup(data, key));
}

static char	*expand_step(char *raw, int *i, t_state *state, t_data *data)
{
	t_state	prev;
	char	buf[2];

	prev = *state;
	state_change(state, raw[*i]);
	if (*state != prev)
	{
		(*i)++;
		return (NULL);
	}
	if (*state != QUOTE && raw[*i] == '$')
		return (expand_dollar(raw, i, data));
	buf[0] = raw[(*i)++];
	buf[1] = '\0';
	return (ft_strdup(buf));
}

char	*expand_word(char *raw, t_data *data)
{
	char	*result;
	t_state	state;
	int		i;
	char	*val;

	result = ft_strdup("");
	state = NORMAL;
	i = 0;
	while (result && raw[i])
	{
		val = expand_step(raw, &i, &state, data);
		if (val)
		{
			result = append_str(result, val);
			free(val);
		}
	}
	return (result);
}
