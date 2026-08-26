/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 04:00:07 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/19 17:10:05 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"

t_redir	*redir_add(char *file, t_token_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = file;
	new_redir->in_quote = 0;
	new_redir->next = NULL;
	return (new_redir);
}

void	redir_add_last(t_redir **list, t_redir *new_redir)
{
	t_redir	*current;

	if (!list || !new_redir)
		return ;
	if (*list == NULL)
	{
		*list = new_redir;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redir;
}
