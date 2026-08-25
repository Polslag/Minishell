/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 23:33:43 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/19 17:10:10 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"

t_command	*command_add_init(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
	{
		return (NULL);
	}
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->fd_out = -1;
	cmd->fd_in = -1;
	cmd->pid = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

void	command_add_last(t_command **list, t_command *new_cmd)
{
	t_command	*current;

	if (!list || !new_cmd)
		return ;
	if (*list == NULL)
	{
		*list = new_cmd;
		return ;
	}
	current = *list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_cmd;
	new_cmd->prev = current;
}

static void	free_redir_list(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		free(redir);
		redir = next;
	}
}

void	free_command_list(t_command **list)
{
	t_command	*current;
	t_command	*next;
	int			i;

	if (!list || !*list)
		return ;
	current = *list;
	while (current)
	{
		next = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
			{
				free(current->argv[i]);
				i++;
			}
			free(current->argv);
		}
		free_redir_list(current->redir);
		free(current);
		current = next;
	}
	*list = NULL;
}

t_command	*parsing_commands(t_token *tokens)
{
	t_token		*current;
	t_command	*list;
	t_command	*cmd;

	current = tokens;
	list = NULL;
	while (current)
	{
		cmd = parse_command(&current);
		if (!cmd)
		{
			free_command_list (&list);
			return (NULL);
		}
		else
		{
			command_add_last (&list, cmd);
		}
	}
	return (list);
}
