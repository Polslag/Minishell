/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:09:14 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/26 03:16:45 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft-pilagach/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
}						t_command;

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
	int					last_return;
}						t_data;

int						ft_strncmp(const char *str1, const char *str2,
							size_t n);

t_token					*lexer(char *line);
int						syntax(t_token *list);
int						handle_word(char *line, int *i, t_token **token_list);
void					handle_operator(char *line, int *i,
							t_token **token_list);
void					state_change(t_state *state, char c);

t_token					*linked_list_add(char *value, t_token_type type);
void					linked_list_add_last(t_token **list,
							t_token *new_token);
void					free_token_list(t_token **list);

t_redir					*redir_add(char *file, t_token_type type);
void					redir_add_last(t_redir **list, t_redir *new_redir);
char					*e_redirbuilder(t_command *cmd);
int						e_redir(t_command *cmd);
void					e_closefds(t_command *cmd);
void					free_command_list(t_command **list);
t_command				*command_add_init(void);
void					command_add_last(t_command **list, t_command *new_cmd);
t_command				*parse_command(t_token **tokenn, t_data *data);
t_command				*parsing_commands(t_token *tokens, t_data *data);
void					init_signals(void);
void					handlesignal(int signal);
int						is_exit(char *input);
t_command				*check_token(char *input, t_data *data);
void					debug(t_command *cmd);
char					*expand_word(char *raw, t_data *data);
//
// built-in
int						ft_pwd(void);
int						ft_cd(char *s, t_env **envi);
int						ft_env(t_env **envi);
int						ft_export(char **arg, t_env **envi);
int						ft_unset(t_env **envi, char **cmd);
int						ft_echo(t_command *cmd);
int						ft_exit(t_data *data);
int						ft_isoperand(char c);
int						ft_is_only_num(char *str);
void					ft_exit_abc(t_data *data);
int						ft_already_key(char *key, t_env **envi);
int						ft_check_key(char *key);
void					ft_change_key(char *s, char *key, t_env **envi);
t_env					*ft_search_key(t_env *envi, char *key);
char					*get_home(t_env *envi);
char					*ft_establish_path(char *s);
void					newpwd(t_env **envi);
void					pwdold(char *oldpwd, t_env **envi);
// split value and key from env
char					*ft_split_key(char **env, int i);
char					*ft_split_value(char **env, int i);
// set-up t_env
int						ft_tablen(char **tab);
void					ft_inienv(t_env **list);
t_env					*ft_lstlast(t_env **list);
void					ft_addenv(t_env **list, char **env, int i);
t_env					*ft_envsetup(int env_len, char **env);
// free t_env
void					ft_freeenv(t_env **envi);
// env_utils
int						get_envlen(t_env *env);
void					ft_strcat(char *dst, char *src);
char					**convert_env_to_array(t_env *env);
char					*ft_getenv_value(t_env *envi, char *key);

int						find_path_env(char **ev);
char					**obtain_path(char **ev);
char					*command_path(char *cmd, char **path);

int						e_pipe(t_command *cmd);
char					*e_execbuilder(t_command *cmd, char **env);
int						check_builtin(t_command *cmd);
int						e_builtin(t_command *cmd, t_data *data);
int						e_child(t_command *cmd, t_data *data);
int						e_fork(t_command *cmd, t_data *data);
int						e_wait(t_command *cmd);
int						exec(t_data *data);

#endif
