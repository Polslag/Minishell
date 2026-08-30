/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 04:11:49 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/31 01:18:23 by ysapelie         ###   ########.fr       */
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
	int	saved_0;
	int	saved_1;
	int	ret;

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

int	e_wait_status(pid_t pid, int status_old)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (128 + WTERMSIG(wstatus));
	return (status_old);
}
