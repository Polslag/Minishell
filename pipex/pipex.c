/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:59:11 by pilagach          #+#    #+#             */
/*   Updated: 2026/04/08 14:59:36 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_child1(t_data *data, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (data->fdin != -1 && data->pipe[1] != -1)
	{
		data->cmd = ft_split(cmd, ' ');
		cmd_path = command_path(data->cmd[0], data->path);
		if (cmd_path != NULL && access(cmd_path, F_OK) == 0)
		{
			if (access(cmd_path, X_OK) == -1)
			{
				freeer(data, cmd_path);
				exit(126);
			}
			dup2(data->fdin, 0);
			dup2(data->pipe[1], 1);
			close_files(data, 2);
			execve(cmd_path, data->cmd, data->envp);
		}
	}
	exiting(data, cmd_path, data->fdin, data->pipe[1]);
}

void	exec_child2(t_data *data, char *cmd)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (data->pipe[0] != -1 && data->fdout != -1)
	{
		data->cmd = ft_split(cmd, ' ');
		cmd_path = command_path(data->cmd[0], data->path);
		if (cmd_path != NULL && access(cmd_path, F_OK) == 0)
		{	
			if (access(cmd_path, X_OK) == -1)
			{
				freeer(data, cmd_path);
				exit(126);
			}
			dup2(data->pipe[0], 0);
			dup2(data->fdout, 1);
			close_files(data, 2);
			execve(cmd_path, data->cmd, data->envp);
		}
	}
	exiting(data, cmd_path, data->pipe[0], data->fdout);
}

int	wait_child(t_data *data, int fid1, int fid2)
{
	int	status;

	close(data->pipe[0]);
	close(data->pipe[1]);
	waitpid(fid1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Child1 process exited with code: %d\n", WEXITSTATUS(status));
	waitpid(fid2, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		ft_printf("Child2 process exited with code: %d\n", WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	forker(t_data *data, char *cmd1, char *cmd2)
{
	int	fork_id;
	int	fork_id2;
	int	r;

	r = 0;
	fork_id = fork();
	if (fork_id == 0)
	{
		exec_child1(data, cmd1);
	}
	else
	{
		fork_id2 = fork();
		if (fork_id2 == 0)
			exec_child2(data, cmd2);
		else
			r = wait_child(data, fork_id, fork_id2);
	}
	if (!data->path)
		r = 0;
	freeer(data, NULL);
	return (r);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		r;

	if (ac != 5)
	{
		ft_printf("Invalid number of argument.\n");
		return (0);
	}
	init_data(&data);
	data.fdin = open(av[1], O_RDONLY);
	data.fdout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	data.envp = envp;
	data.path = obtain_path(envp);
	if ((!access(av[2], F_OK) || !access(av[3], F_OK)) && !data.path)
	{
		ft_printf("Malloc failed.\n");
		close_files(&data, 0);
		freeer(&data, NULL);
		return (0);
	}
	pipe(data.pipe);
	r = forker(&data, av[2], av[3]);
	close_files(&data, 2);
	return (r);
}
