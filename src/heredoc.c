/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 12:49:36 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/28 16:36:30 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *limiter)
{
	char *str;
	char *buff;
	char *temp1;
	char *temp2;
	int fd_pipe[2];
	
	str = ft_strdup("");
	if(!str)
	{
		return(-1);
	}
	while(1)
	{
		buff = readline(">");
		if(!buff)
		{
			break;
		}
		if (ft_strncmp(buff,limiter,ft_strlen(limiter) + 1) == 0)
		{
			free(buff);
			break;
		}
		temp1 = ft_strjoin(str,buff);
		temp2 = ft_strjoin(temp1,"\n");

		free(buff);
		free(str);
		free(temp1);

		str = temp2;
	}

	if(pipe(fd_pipe) ==- 1)
	{
		free(str);
		return(1);
	}


	write(fd_pipe[1], str, ft_strlen(str));

	free(str);

	close(fd_pipe[1]);

	return (fd_pipe[0]);


}


