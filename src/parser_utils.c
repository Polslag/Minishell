/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 03:45:28 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/31 01:18:49 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_type(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

void	redir_mark_quote(t_redir *new_redir, t_token *current)
{
	int	j;

	j = 0;
	while (new_redir && current->type == TOKEN_HEREDOC
		&& current->next->value[j])
	{
		if (current->next->value[j] == '\''
			|| current->next->value[j] == '"')
			new_redir->in_quote = 1;
		j++;
	}
}

static int	keep_word(char *val, char *raw)
{
	return (val[0] || ft_strchr(raw, '\'') || ft_strchr(raw, '"'));
}

int	add_word(char **argv, int *i, t_token *current, t_data *data)
{
	char	*val;

	val = expand_word(current->value, data);
	if (!val)
	{
		argv[*i] = NULL;
		ft_free_tab(argv);
		return (1);
	}
	if (keep_word(val, current->value))
		argv[(*i)++] = val;
	else
		free(val);
	return (0);
}
