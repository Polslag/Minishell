/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 07:20:00 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/28 14:59:23 by pilagach         ###   ########.fr       */
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
		ret = ft_exit(data, 0);
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
