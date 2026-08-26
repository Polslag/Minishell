/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/23 16:57:57 by pilagach          #+#    #+#             */
/*   Updated: 2026/08/26 03:39:33 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*e_execbuilder(t_command *cmd, char **env)
{
	char	**envpath;
	char	*path;

	envpath = obtain_path(env);
	if (!envpath)
		return (NULL);
	path = NULL;
	path = command_path(cmd->argv[0], envpath);
	return (path);
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
	printf("%s\n", path);
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

int	check_builtin(t_command *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "echo") || !ft_strcmp(cmd->argv[0], "cd")
		|| !ft_strcmp(cmd->argv[0], "env") || !ft_strcmp(cmd->argv[0], "pwd")
		|| !ft_strcmp(cmd->argv[0], "export") || !ft_strcmp(cmd->argv[0],
			"unset") || !ft_strcmp(cmd->argv[0], "exit"))
		return (0);
	return (1);
}

int	e_builtin(t_command *cmd, t_data *data)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(cmd->argv[0], "cd"))
		ret = ft_cd(cmd->argv[1], &(data->envi));
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ret = ft_env(&(data->envi));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ret = ft_export(cmd->argv, &(data->envi));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		ret = ft_pwd();
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ret = ft_unset(&(data->envi), cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		ret = ft_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ret = ft_exit(data);
	return (ret);
}

int	e_child(t_command *cmd, t_data *data)
{
	char	*cmdpath;
	char	**env;
	int		ret;

	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	if (check_builtin(cmd) == 0)
	{
		ret = e_builtin(cmd, data);
		exit(ret);
	}
	env = convert_env_to_array(data->envi);
	cmdpath = e_execbuilder(cmd, env);
	execve(cmdpath, cmd->argv, env);
	exit(127);
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
				e_builtin(node, data);

				dup2(saved_0, 0);
				dup2(saved_1, 1);
				close(saved_0);
				close(saved_1);
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