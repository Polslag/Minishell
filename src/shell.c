/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:46:42 by ysapelie          #+#    #+#             */
/*   Updated: 2026/09/01 16:27:03 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int	g_signal = 0;

void	handlesignal(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handlesignal);
	signal(SIGQUIT, SIG_IGN);
}

int	apply_signal(int ret)
{
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (130);
	}
	return (ret);
}

t_command	*check_token(char *input, t_data *data)
{
	t_token		*tokens;
	t_command	*cmd;
	int			err;

	tokens = lexer(input, &err);
	if (tokens == NULL)
	{
		if (err)
			syntax_error(data);
		free(input);
		return (NULL);
	}
	if(syntax(tokens) == 5)
	{
		open(tokens->next->next->next->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (syntax(tokens))
	{
		free_token_list(&tokens);
		syntax_error(data);
		free(input);
		return (NULL);
	}
	cmd = parsing_commands(tokens, data);
	free_token_list(&tokens);
	free(input);
	return (cmd);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_data		*data;

	(void)ac;
	(void)av;
	data = init_data(env);
	if (!data)
	{
		ft_free_data(data);
		free(data);
		return (1);
	}
	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			ft_exit(NULL, data, 1);
		data->last_return = apply_signal(data->last_return);
		if (input[0] != '\0')
			add_history(input);
		free_command_list(&data->cmd);
		data->cmd = check_token(input, data);
		if (data->cmd)
			data->last_return = apply_signal(exec(data));
	}
	rl_clear_history();
}
