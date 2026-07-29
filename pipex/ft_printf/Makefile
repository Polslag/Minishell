CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

AR = ar rsc

SRC = ft_printf.c ft_utils_call_one.c ft_utils_call_two.c ft_putchar.c ft_checkbase.c \
	ft_putstrc.c ft_putptrc.c ft_putnbrc_base.c ft_putnbrc_uint.c ft_puthexc.c \
	ft_strlen.c

OBJ = ${SRC:.c=.o}

.PHONY:	all clean fclean re

all:	${NAME}

${NAME}:	${OBJ}
	${AR} ${NAME} ${OBJ}

%.o:	%.c
	${CC} ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJ}

fclean:	clean
	rm -f ${NAME}

re:	fclean all
