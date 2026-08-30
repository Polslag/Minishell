/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 04:00:07 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 22:36:12 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_redir_open(t_redir *redir, t_data *data)
{
	if (redir->type == TOKEN_REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == TOKEN_APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == TOKEN_REDIR_IN)
		return (open(redir->file, O_RDONLY));
	return (heredoc(redir->file, redir->in_quote, data));
}

void	e_redir_bind(t_command *cmd, t_redir *redir, int fd)
{
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
	{
		if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = fd;
	}
	else
	{
		if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = fd;
	}
}

int	e_redir_apply(t_command *cmd, t_redir *redir, t_data *data)
{
	int	fd;

	fd = e_redir_open(redir, data);
	if (fd == -1)
		return (-1);
	e_redir_bind(cmd, redir, fd);
	return (fd);
}

int	e_redir(t_command *cmd, t_data *data)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir;
	while (redir)
	{
		fd = e_redir_apply(cmd, redir, data);
		if (fd == -1)
		{
			if (redir->type != TOKEN_HEREDOC)
				e_redir_error(redir->file);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
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
