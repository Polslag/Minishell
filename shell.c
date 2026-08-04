/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:46:42 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/04 17:50:48 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include "minishell.h"
#include "libft-pilagach/libft.h"


void handleSignal(int signal)
{
	if(signal == SIGINT )
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }

}

int main()
{
	char* input;
	
	signal(SIGINT, handleSignal);
    signal(SIGQUIT, SIG_IGN);

	
	while(1)
	{
		input = readline("minishell$ ");
        
        if (input == NULL) {
            printf("%s\n","exit");
            break;
        }

        if (!ft_strncmp(input,"exit\0",5))
        {
            printf("%s\n","exit");
            break;
        }

		if (ft_strlen(input) == 0) {
             printf("%s", input);
        }
        else
        {
            printf("%s\n", input);  

        }

        if (input[0] != '\0') {
            add_history(input);
        }

        free(input);
    }
	return (0);
}