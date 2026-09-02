/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 04:11:49 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/01 14:49:18 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	e_skip(t_command *node, int pid)
{
	node->pid = pid;
	e_closefds(node);
}

void	e_setup_fds(t_command *node, t_command *first)
{
	if (node == first)
		node->fd_in = STDIN_FILENO;
	if (node->next)
		e_pipe(node);
	else
		node->fd_out = STDOUT_FILENO;
}

int	e_exec_direct(t_command *node, t_data *data)
{
	int	ret;

	data->saved_in = dup(0);
	data->saved_out = dup(1);
	dup2(node->fd_in, 0);
	dup2(node->fd_out, 1);
	ret = e_builtin(node, data);
	dup2(data->saved_in, 0);
	dup2(data->saved_out, 1);
	close(data->saved_in);
	close(data->saved_out);
	data->saved_in = -1;
	data->saved_out = -1;
	e_closefds(node);
	return (ret);
}

int	e_wait_status(pid_t pid, int status_old, int *quit)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGQUIT && !*quit)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			*quit = 1;
		}
		return (128 + WTERMSIG(wstatus));
	}
	return (status_old);
}
