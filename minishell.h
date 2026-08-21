/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:09:14 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/19 17:10:08 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft-pilagach/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_state
{
	NORMAL,
	QUOTE,
	DBLQUOTE
}						t_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}						t_token_type;

typedef struct s_redir
{
	t_token_type		type;
	char				*file;
	int					in_quote;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				**argv;
	t_redir				*redir;
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_command	*next;
	struct s_command	*prev;
}					t_command;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

int						ft_strncmp(const char *str1, const char *str2,
							size_t n);

t_token					*lexer(char *line);
int						syntax(t_token *list);
int						handle_word(char *line, int *i, t_token **token_list);
void					handle_operator(char *line, int *i,
							t_token **token_list);

t_token					*linked_list_add(char *value, t_token_type type);
void					linked_list_add_last(t_token **list,
							t_token *new_token);
void					free_token_list(t_token **list);

t_redir					*redir_add(char *file, t_token_type type);
void					redir_add_last(t_redir **list, t_redir *new_redir);
void					free_command_list(t_command **list);
t_command				*command_add_init(void);
void					command_add_last(t_command **list, t_command *new_cmd);
t_command				*parse_command(t_token **tokenn);
t_command				*parsing_commands(t_token *tokens);
void					init_signals(void);
void					handlesignal(int signal);
int						is_exit(char *input);
void					check_token(char *input);
void					debug(t_command *cmd);

#endif
