/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:41:31 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/04 17:50:51 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_word(char *line, int *i, t_token **token_list)
{
    int     start;
    t_state state;
    char    *word;

    start = *i;
    state = NORMAL;
    while (line[*i] != '\0')
    {
        
        if (state == NORMAL && line[*i] == '\'')
            state = QUOTE;
        else if (state == NORMAL && line[*i] == '\"')
            state = DBLQUOTE;
        else if (state == QUOTE && line[*i] == '\'')
            state = NORMAL;
        else if (state == DBLQUOTE && line[*i] == '\"')
            state = NORMAL;
        else if (state == NORMAL && (line[*i] == ' ' || line[*i] == '\t' || 
            line[*i] == '|' || line[*i] == '<' || line[*i] == '>'))
        {
            break;
        }
        (*i)++;
    }
    if(state != NORMAL)
        return(1);
    word = ft_substr(line, start, *i - start);
    linked_list_add_last(token_list, linked_list_add(word, TOKEN_WORD));
    return(0);
    
}

void handle_operator(char *line, int *i, t_token **token_list)
{
    int     start;

    start = *i;
    
    if(line[*i] == '<' && line[*i + 1] == '<')
    {
        linked_list_add_last(token_list, linked_list_add(ft_strdup("<<"), TOKEN_HEREDOC));
        (*i)= (*i) + 2 ;
    }
    else if(line[*i] == '>' && line[*i + 1] == '>')
    {
        linked_list_add_last(token_list, linked_list_add(ft_strdup(">>"), TOKEN_APPEND));
        (*i)= (*i) + 2 ;
    }
    else if(line[*i] == '>')
    {
        linked_list_add_last(token_list, linked_list_add(ft_strdup(">"), TOKEN_REDIR_OUT));
        (*i)++;
    }
    else if(line[*i] == '<')
    {
        linked_list_add_last(token_list, linked_list_add(ft_strdup("<"), TOKEN_REDIR_IN));
        (*i)++;
    }
    else if(line[*i] == '|')
    {
        linked_list_add_last(token_list, linked_list_add(ft_strdup("|"), TOKEN_PIPE));
        (*i)++;
    }

}