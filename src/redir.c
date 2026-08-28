/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 04:00:07 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/28 10:27:40 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*e_redirbuilder(t_command *cmd)
{
	char	*path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	path = (char *)ft_calloc(sizeof(char), (ft_strlen(cwd)
				+ ft_strlen(cmd->redir->file) + 2));
	ft_strcat(path, cwd);
	ft_strcat(path, "/");
	ft_strcat(path, cmd->redir->file);
	// printf("%s\n", path);
	free(cwd);
	return (path);
}

int	e_redir(t_command *cmd)
{
	int		fd;
	char	*path;

	path = e_redirbuilder(cmd);
	if (cmd->redir->type == TOKEN_REDIR_OUT || cmd->redir->type == TOKEN_APPEND)
	{
		if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
		{
			close(cmd->fd_out);
		}
		if (cmd->redir->type == TOKEN_REDIR_OUT)
		{
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		cmd->fd_out = fd;
	}
	else if (cmd->redir->type == TOKEN_REDIR_IN)
	{
		if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
		{
			close(cmd->fd_in);
		}
		fd = open(path, O_RDONLY);
		cmd->fd_in = fd;
	}
	free(path);
	return (fd == -1);
}

void	e_closefds(t_command *cmd)
{
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}
