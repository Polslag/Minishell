/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 03:44:59 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/01 16:52:07 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	ft_free_cmd(t_command *cmd)
{
	t_command	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
			ft_free_tab(cmd->argv);
		ft_free_redir(cmd->redir);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_freeenv(t_env **envi)
{
	t_env	*bob;

	while ((*envi))
	{
		bob = (*envi)->next;
		free((*envi)->key);
		free((*envi)->value);
		free((*envi));
		(*envi) = bob;
	}
	free((*envi));
}

void	ft_free_data(t_data *data)
{
	if (data->cmd)
		e_closefds(data->cmd);
	ft_freeenv(&(data->envi));
	ft_free_cmd(data->cmd);
	data->cmd = NULL;
	free(data);
	rl_clear_history();
}
