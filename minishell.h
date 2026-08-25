/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <pilagach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:09:14 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/24 14:23:37 by pilagach         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

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

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	t_command			*cmd;
	t_env				*envi;
}						t_data;

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
t_command				*check_token(char *input);
void					debug(t_command *cmd);
//
//built-in
int						ft_pwd(void);
int						ft_cd(char *s, t_env **envi);
int						ft_env(t_env **envi);
int						ft_export(char **arg, t_env **envi);
int						ft_unset(t_env **envi, char **cmd);
int						ft_echo(t_command *cmd);
int						ft_exit(t_data *data);
//split value and key from env
char					*ft_split_key(char **env, int i);
char					*ft_split_value(char **env, int i);
//set-up t_env
int						ft_tablen(char **tab);
void					ft_addenv(t_env **list, char **env, int i);
t_env					*ft_envsetup(int env_len, char **env);
//free t_env
void					ft_freeenv(t_env **envi);
//env_utils
void					ft_strcat(char *dst, char *src);
char					**convert_env_to_array(t_env *env);

int						find_path_env(char **ev);
char					**obtain_path(char **ev);
char					*command_path(char *cmd, char **path);

void					exec(t_data *data);

#endif
