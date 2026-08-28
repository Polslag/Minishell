/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:57:57 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/28 07:23:08 by ysapelie         ###   ########.fr       */
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

int	e_wait(t_command *cmd)
{
	int	wstatus;
	int	g_error;

	wstatus = 0;
	g_error = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			waitpid(cmd->pid, &wstatus, 0);
			if (WIFEXITED(wstatus))
				g_error = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				g_error = 128 + WTERMSIG(wstatus);
		}
		else if (cmd->pid == -1)
			g_error = 1;
		cmd = cmd->next;
	}
	return (g_error);
}

int	exec(t_data *data)
{
	t_command *node;
	int err;
	int saved_0;
	int saved_1;
	int ret;

	node = data->cmd;
	err = 0;
	(void)err;
	while (node)
	{
		// printf("passage N%d\n", i++);
		if (node == data->cmd)
			node->fd_in = STDIN_FILENO;
		if (node->next)
			err = e_pipe(node);
		else
			node->fd_out = STDOUT_FILENO;
		if (node->redir && e_redir(node))
		{
			node->pid = -1;
			e_closefds(node);
			node = node->next;
			continue ;
		}
		if (!node->argv[0])
		{
			node->pid = 0;
			e_closefds(node);
			node = node->next;
			continue ;
		}
		if (check_builtin(node) == 0)
		{
			if (node == data->cmd && node->next == NULL)
			{
				saved_0 = dup(0);
				saved_1 = dup(1);

				dup2(node->fd_in, 0);
				dup2(node->fd_out, 1);
				ret = e_builtin(node, data);

				dup2(saved_0, 0);
				dup2(saved_1, 1);
				close(saved_0);
				close(saved_1);
				e_closefds(node);
				return (ret);
			}
			else
				e_fork(node, data);
		}
		else
			e_fork(node, data);
		e_closefds(node);
		node = node->next;
	}
	return (e_wait(data->cmd));
}