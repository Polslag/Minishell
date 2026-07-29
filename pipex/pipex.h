/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 14:00:10 by pilagach          #+#    #+#             */
/*   Updated: 2026/04/01 15:46:08 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "ft_printf/ft_printf.h"

typedef struct s_data
{
	char	**path;
	char	**envp;
	char	**cmd;
	int		fdin;
	int		fdout;
	int		pipe[2];
}				t_data;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);

void	free_cmd(t_data *data);
void	free_path(t_data *data);
void	freeer(t_data *data, char *cp);
void	exiting(t_data *data, char *cp, int fdin, int fdout);
int		close_files(t_data *data, int flag);

void	init_data(t_data *data);

int		find_path_env(char **ev);
char	**obtain_path(char **ev);
char	*command_path(char *cmd, char **path);

#endif