/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:41:31 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 23:58:34 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_change(t_state *state, char c)
{
	if (*state == NORMAL && c == '\'')
		*state = QUOTE;
	else if (*state == NORMAL && c == '\"')
		*state = DBLQUOTE;
	else if (*state == QUOTE && c == '\'')
		*state = NORMAL;
	else if (*state == DBLQUOTE && c == '\"')
		*state = NORMAL;
}

int	handle_word(char *line, int *i, t_token **token_list)
{
	int		start;
	t_state	state;
	char	*word;

	start = *i;
	state = NORMAL;
	while (line[*i] != '\0')
	{
		state_change(&state, line[*i]);
		if (state == NORMAL && (line[*i] == ' ' || line[*i] == '\t'
				|| line[*i] == '|' || line[*i] == '<' || line[*i] == '>'))
		{
			break ;
		}
		(*i)++;
	}
	if (state != NORMAL)
		return (1);
	word = ft_substr(line, start, *i - start);
	if (!word)
		return (1);
	linked_list_add_last(token_list, linked_list_add(word, TOKEN_WORD));
	return (0);
}

static int	add_op(t_token **lst, char *op, int type, int occ)
{
	linked_list_add_last(lst, linked_list_add(ft_strdup(op), type));
	return (occ);
}

void	handle_operator(char *line, int *i, t_token **token_list)
{
	if (line[*i] == '<' && line[*i + 1] == '<')
		*i += add_op(token_list, "<<", TOKEN_HEREDOC, 2);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		*i += add_op(token_list, ">>", TOKEN_APPEND, 2);
	else if (line[*i] == '>')
		*i += add_op(token_list, ">", TOKEN_REDIR_OUT, 1);
	else if (line[*i] == '<')
		*i += add_op(token_list, "<", TOKEN_REDIR_IN, 1);
	else if (line[*i] == '|')
		*i += add_op(token_list, "|", TOKEN_PIPE, 1);
}
