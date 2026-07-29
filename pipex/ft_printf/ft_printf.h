/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilagach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:10:05 by pilagach          #+#    #+#             */
/*   Updated: 2025/12/09 15:10:59 by pilagach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef int	(*t_type)(va_list *ap);

typedef struct t_fn
{
	char	flag;
	t_type	function;
}				t_fn;

int		ft_printf(const char *input, ...);
int		ft_checkflag(va_list *ap, char flag);

int		c_caller(va_list *ap);
int		s_caller(va_list *ap);
int		p_caller(va_list *ap);
int		d_caller(va_list *ap);
int		i_caller(va_list *ap);
int		u_caller(va_list *ap);
int		xlow_caller(va_list *ap);
int		xup_caller(va_list *ap);

void	ft_putchar(char c);
int		ft_strlen(const char *str);
int		ft_putstrc(char *s);
int		ft_checkbase(char *base);
int		ft_printptr(size_t hex, char *base);
int		ft_putptrc(void *ptr);
int		ft_putnbrc_base(int n, char *base);
int		ft_putnbrc_uint(unsigned int n);
int		ft_puthexc(unsigned int hex, char *base);

#endif
