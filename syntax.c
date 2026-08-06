/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:39:20 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/06 18:19:59 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int syntax(t_token *list)
{
	t_token *current;
	
	current = list;

	while(current)
	{
		if(current->type == TOKEN_PIPE && (current->prev == NULL || current->next == NULL || current->next->type == TOKEN_PIPE ))
		{
			return(1);
		}
		else if((current->type == TOKEN_APPEND || current->type == TOKEN_HEREDOC || current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT) 
		&& ((current->next == NULL) || (current->next->type != TOKEN_WORD)))
		{
			return(1);
		}
		current = current->next;
	}

	return(0);
}