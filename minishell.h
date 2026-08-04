/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysapelie <ysapelie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 16:09:14 by ysapelie          #+#    #+#             */
/*   Updated: 2026/08/04 17:50:36 by ysapelie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft-pilagach/libft.h"


typedef enum e_state {
    NORMAL,
    QUOTE,
    DBLQUOTE
} t_state;

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND
}   t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

int ft_strncmp(const char* str1,const char* str2,size_t n);