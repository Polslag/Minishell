/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 07:20:00 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/01 14:26:31 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*e_execbuilder(t_command *cmd, char **env)
{
	char	**envpath;
	char	*path;

	envpath = obtain_path(env);
	path = command_path(cmd->argv[0], envpath);
	if (envpath)
		ft_free_tab(envpath);
	return (path);
}

int	check_builtin(t_command *cmd)
{
	if (!cmd->argv[0])
		return (1);
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
		ret = ft_cd(cmd, &(data->envi));
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
		ret = ft_exit(cmd, data, 0);
	return (ret);
}

void	e_childfds(t_command *cmd, t_command *list)
{
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	while (list)
	{
		if (list != cmd)
		{
			if (list->fd_in > 2)
				close(list->fd_in);
			if (list->fd_out > 2)
				close(list->fd_out);
		}
		list = list->next;
	}
}

int	e_child(t_command *cmd, t_data *data)
{
	char		*cmdpath;
	char		**env;
	int			ret;
	struct stat	st;

	e_childfds(cmd, data->cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_builtin(cmd) == 0)
	{
		ret = e_builtin(cmd, data);
		ft_free_data(data);
		exit(ret);
	}
	env = convert_env_to_array(data->envi);
	cmdpath = e_execbuilder(cmd, env);
	if (cmdpath && stat(cmdpath, &st) == 0 && S_ISDIR(st.st_mode))
		errno = EISDIR;
	else if (cmdpath)
		execve(cmdpath, cmd->argv, env);
	free(cmdpath);
	ft_free_tab(env);
	exit(e_exec_fail(cmd->argv[0], cmdpath != NULL, data));
}
