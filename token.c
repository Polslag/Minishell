/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 17:21:44 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/04 17:50:56 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft-pilagach/libft.h"


t_token *linked_list_add(char* value,t_token_type type)
{
	t_token *new_node;

    new_node = malloc(sizeof(t_token));
    
    if (!new_node)
        return (NULL);

    new_node->value = value;
    new_node->type = type;
    
    new_node->next = NULL;
    new_node->prev = NULL;

    return (new_node);
}

t_token *linked_list_add_last(t_token **list, t_token *new_token)
{
	t_token *current;

    if (!list || !new_token)
        return ;
    if (*list == NULL)
    {
        *list = new_token;  
        return ;
    }
    current = *list;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_token;
    new_token->prev = current;
}

void free_token_list(t_token **list)
{
    t_token *current;
    t_token *next;

    if (!list || !*list)
        return ;
    current = *list;
    while (current)
    {
        next = current->next;
        if (current->value)
            free(current->value);
        free(current);          
        current = next;
    }
    *list = NULL;
}

t_token *lexer(char *line)
{
	t_token *token_list;
	int	i;
	
	token_list = NULL;
	i = 0;
	while(line[i] != '\0')
	{
		while(line[i] == ' ' || line[i] == '\t')
			i++;
		
		if (line[i] == '\0')
    		break;

		if (line[i] == '|' || line[i] == '<' ||  line[i] == '>')
		{
			// if(line[i] == line[i+1])
			// 	i = i +2;
			// else 
			// 	i = i + 1;
			handle_operator(line, &i, &token_list);
		}
		else 
		{
			if(handle_word(line, &i, &token_list) == 1)
            {
                printf("%s","error");
                free_token_list(token_list);
                return(NULL);
            }
		}
	}
	return(token_list);
}