CC = cc

FLAGS = -Wall -Wextra -Werror

NAME = pipex

SRC = pipex.c ft_split.c utils.c utils_path.c free.c

OBJ = ${SRC:.c=.o}

LIB = ft_printf/libftprintf.a

.PHONY:	all clean fclean re

all:	${NAME}

%.o:	%.c
	${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJ}
	make -C ft_printf
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${LIB}

clean:
	rm -f ${OBJ}

fclean:	clean
	make fclean -C ft_printf
	rm -f ${NAME}

re:	fclean all
