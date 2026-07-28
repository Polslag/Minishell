/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:46:42 by ysapelie          #+#    #+#             */
/*   Updated: 2026/07/28 15:55:53 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handleSignal(int signal)
{
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


int main()
{
	char* input;
	
	signal(SIGINT, handleSignal);
	
	while(1)
	{
		input = readline("minishell>");
		
		if (input == NULL) {
            printf("\n");
            break;
        }
	
		printf("%s\n", input);

        if (input[0] != '\0') {
            add_history(input);
        }

        free(input);
    }
	return (0);
}