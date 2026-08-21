/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:25:00 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/19 17:10:07 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"

static int	is_redir_type(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND);
}

static t_token	*walk_segment(t_token *start, int *count)
{
	t_token	*current;

	current = start;
	*count = 0;
	while (current && current->type != TOKEN_PIPE)
	{
		if (is_redir_type(current->type))
			current = current->next->next;
		else
		{
			(*count)++;
			current = current->next;
		}
	}
	return (current);
}

static char	**build_argv(t_token *start, int count)
{
	char	**argv;
	t_token	*current;
	int		i;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	current = start;
	i = 0;
	while (current && current->type != TOKEN_PIPE)
	{
		if (is_redir_type(current->type))
			current = current->next->next;
		else
		{
			argv[i++] = ft_strdup(current->value);
			current = current->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}

static void	build_redir(t_token *start, t_command *cmd)
{
	t_token	*current;
	char	*file;

	current = start;
	while (current && current->type != TOKEN_PIPE)
	{
		if (is_redir_type(current->type))
		{
			file = ft_strdup(current->next->value);
			redir_add_last(&cmd->redir, redir_add(file, current->type));
			current = current->next->next;
		}
		else
			current = current->next;
	}
}

t_command	*parse_command(t_token **token)
{
	t_token		*seg_start;
	t_token		*end;
	t_command	*cmd;
	int			count;

	seg_start = *token;
	end = walk_segment(seg_start, &count);
	cmd = command_add_init();
	if (!cmd)
		return (NULL);
	cmd->argv = build_argv(seg_start, count);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	build_redir(seg_start, cmd);
	if (end)
		*token = end->next;
	else
		*token = NULL;
	return (cmd);
}
