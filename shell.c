/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:46:42 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/21 14:26:26 by ysapelie         ###   ########.fr       */
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
	if (!ft_strncmp(input, "exit\0", 5) || !ft_strncmp(input, "exit ", 5))
		return (1);
	return (0);
}

void	check_token(char *input)
{
	t_token		*tokens;
	t_command	*cmd;

	tokens = lexer(input);
	if (tokens == NULL)
	{
		free(input);
		return ;
	}
	if (syntax(tokens))
	{
		free_token_list(&tokens);
		printf("%s\n", "error");
		free(input);
		return ;
	}
	cmd = parsing_commands(tokens);
	free_token_list(&tokens);
	if (cmd == NULL)
	{
		free(input);
		return ;
	}
	free_command_list(&cmd);
	free(input);
}

int	main(void)
{
	char	*input;

	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (is_exit(input))
		{
			printf("%s\n", "exit");
			free(input);
			break ;
		}
		if (input[0] != '\0')
		{
			add_history(input);
		}
		check_token(input);
	}
	return (0);
}
