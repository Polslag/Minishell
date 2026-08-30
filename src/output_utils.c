/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 22:35:33 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/30 22:35:33 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char *s)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(s, 2);
	if (!access(s, F_OK))
		ft_putstr_fd(": Not a directory\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
}

void	e_redir_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error_output(t_data *data, char *title, char *content, char *color)
{
	(void)data;
	(void)color;
	if (title)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(title, 2);
		ft_putstr_fd(" ", 2);
	}
	ft_putstr_fd(content, 2);
}

int	e_exec_fail(char *cmd, int found)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	if (!found)
	{
		ft_putstr_fd("command not found\n", 2);
		return (127);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC)
		return (126);
	return (127);
}
