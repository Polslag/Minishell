/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:57:57 by pilagach          #+#    #+#             */
/*   Updated: 2026/09/01 14:19:50 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_pipe(t_command *cmd)
{
	int	fd[2];

	pipe(fd);
	if (!fd[0] || !fd[1])
		return (1);
	cmd->fd_out = fd[1];
	cmd->next->fd_in = fd[0];
	return (0);
}

int	e_fork(t_command *cmd, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
		e_child(cmd, data);
	return (0);
}

void	wait_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
}

int	e_wait(t_command *cmd)
{
	int	g_error;
	int	quit;

	g_error = 0;
	quit = 0;
	signal(SIGINT, wait_sigint);
	while (cmd)
	{
		if (cmd->pid > 0)
			g_error = e_wait_status(cmd->pid, g_error, &quit);
		else if (cmd->pid == -1)
			g_error = 1;
		else
			g_error = 0;
		cmd = cmd->next;
	}
	signal(SIGINT, handlesignal);
	if (g_signal == SIGINT)
		write(2, "\n", 1);
	return (g_error);
}

int	exec(t_data *data)
{
	t_command	*node;

	node = data->cmd;
	while (node)
	{
		e_setup_fds(node, data->cmd);
		if (node->redir && e_redir(node, data))
			e_skip(node, -1);
		else if (!node->argv[0])
			e_skip(node, 0);
		else if (check_builtin(node) == 0
			&& node == data->cmd && node->next == NULL)
			return (e_exec_direct(node, data));
		else
		{
			e_fork(node, data);
			e_closefds(node);
		}
		node = node->next;
	}
	return (e_wait(data->cmd));
}
