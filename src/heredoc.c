/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 12:49:36 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/31 00:47:33 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_all(int fd, char *s)
{
	size_t	len;
	size_t	off;
	ssize_t	n;

	len = ft_strlen(s);
	off = 0;
	while (off < len)
	{
		n = write(fd, s + off, len - off);
		if (n < 0)
			return (-1);
		off = off + n;
	}
	return (0);
}

char	*heredoc_body(char *limiter, int in_quote, t_data *data)
{
	char	*str;
	char	*buff;

	str = ft_strdup("");
	buff = readline(">");
	while (str && buff)
	{
		if (ft_strncmp(buff, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(buff);
			return (str);
		}
		buff = heredoc_maybe_expand(buff, in_quote, data);
		if (!buff)
		{
			free(str);
			return (NULL);
		}
		str = heredoc_append(str, buff);
		buff = readline(">");
	}
	free(buff);
	return (str);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "^C\n", 3);
	close(STDIN_FILENO);
}

int	heredoc_pipe(char *str)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		free(str);
		return (-1);
	}
	if (write_all(fd_pipe[1], str) < 0)
	{
		free(str);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		return (-1);
	}
	free(str);
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}

int	heredoc(char *limiter, int in_quote, t_data *data)
{
	char	*str;
	int		saved;

	saved = dup(STDIN_FILENO);
	g_signal = 0;
	signal(SIGINT, heredoc_sigint);
	str = heredoc_body(limiter, in_quote, data);
	signal(SIGINT, handlesignal);
	dup2(saved, STDIN_FILENO);
	close(saved);
	if (g_signal == SIGINT || !str)
	{
		free(str);
		return (-1);
	}
	return (heredoc_pipe(str));
}
