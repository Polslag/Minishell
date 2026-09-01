/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 22:25:00 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/31 01:18:54 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"

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

static char	**build_argv(t_token *start, int count, t_data *data)
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
			if (add_word(argv, &i, current, data))
				return (NULL);
			current = current->next;
		}
	}
	argv[i] = NULL;
	return (argv);
}

static int	build_redir(t_token *start, t_command *cmd, t_data *data)
{
	t_token	*current;
	t_redir	*new_redir;
	char	*file;

	current = start;
	while (current && current->type != TOKEN_PIPE)
	{
		if (is_redir_type(current->type))
		{
			file = expand_word(current->next->value, data);
			if (!file)
				return (0);
			new_redir = redir_add(file, current->type);
			redir_mark_quote(new_redir, current);
			redir_add_last(&cmd->redir, new_redir);
			current = current->next->next;
		}
		else
			current = current->next;
	}
	return (1);
}

static int	fill_command(t_command *cmd, t_token *seg_start, int count,
		t_data *data)
{
	cmd->argv = build_argv(seg_start, count, data);
	if (!cmd->argv)
		return (0);
	return (build_redir(seg_start, cmd, data));
}

t_command	*parse_command(t_token **token, t_data *data)
{
	t_token		*seg_start;
	t_token		*end;
	t_command	*cmd;
	int			count;

	seg_start = *token;
	end = walk_segment(seg_start, &count);
	cmd = command_add_init();
	if (!cmd || !fill_command(cmd, seg_start, count, data))
	{
		free_command_list(&cmd);
		return (NULL);
	}
	if (end)
		*token = end->next;
	else
		*token = NULL;
	return (cmd);
}
