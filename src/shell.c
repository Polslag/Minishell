/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:46:42 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/28 17:59:38 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	handlesignal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, handlesignal);
	signal(SIGQUIT, SIG_IGN);
}

int	is_exit(char *input)
{
	if (input == NULL)
		return (1);
	if (!ft_strcmp(input, "exit\0") || !ft_strcmp(input, "exit "))
		return (1);
	return (0);
}

t_command	*check_token(char *input, t_data *data)
{
	t_token		*tokens;
	t_command	*cmd;

	tokens = lexer(input);
	if (tokens == NULL)
	{
		free(input);
		return (NULL);
	}
	if (syntax(tokens))
	{
		free_token_list(&tokens);
		printf("%s\n", "error");
		free(input);
		return (NULL);
	}
	cmd = parsing_commands(tokens, data);
	free_token_list(&tokens);
	if (cmd == NULL)
	{
		free(input);
		return (NULL);
	}
	free(input);
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_data		*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	data->cmd = NULL;
	data->envi = ft_envsetup(ft_tablen(env), env);
	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			ft_exit(data, 1);
		if (input[0] != '\0')
			add_history(input);
		data->cmd = check_token(input, data);
		data->last_return = exec(data);
	}
	rl_clear_history();
	ft_freeenv(&data->envi);
	free_command_list(&data->cmd);
	free(data);
	return (0);
}
