# **************************************************************************** #
# COLORS

GREEN        := \033[0;92m
YELLOW        := \033[0;93m
BLUE        := \033[0;94m
END_COLOR    := \033[0;39m

# **************************************************************************** #
# VARIABLES

SRCS    =    handle.c \
            exec.c \
            debug.c \
            command.c \
            parser.c \
            redir.c \
            shell.c \
            syntax.c \
            token.c \
			env_setup.c \
			env_split.c \
			free_env.c \
			env_utils.c \
			utils_path.c \
			built-in/ft_cd.c \
			built-in/ft_echo.c \
			built-in/ft_env.c \
			built-in/ft_exit.c \
			built-in/ft_export.c \
			built-in/ft_pwd.c \
			built-in/ft_unset.c
OBJ        =    ${SRCS:.c=.o}
HEADER    =   minishell.h
NAME    =    minishell
LIB        =    libft-pilagach/libft.a
CC        =    cc
CFLAGS    =    -Wall -Wextra -Werror

# **************************************************************************** #
# RULES

%.o:    %.c
	@${CC} ${CFLAGS} -c -g $< -o $@
	@echo -e "$(BLUE)Compiling $<...$(END_COLOR)"

$(NAME):    ${OBJ} Makefile
	@make --no-print-directory -C libft-pilagach all
	@make --no-print-directory -C libft-pilagach clean
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) -l readline
	@rm -f ${OBJ}
	@echo -e "$(GREEN)Compiled $(NAME) :)$(END_COLOR)"

all:    ${NAME}

clean:
	@rm -f ${OBJ}
	@echo -e "$(YELLOW)Removed object files.$(END_COLOR)"

fclean: clean
	@rm -f ${NAME}
	@echo -e "$(YELLOW)Cleaned libraries and $(NAME) executable.$(END_COLOR)"

re:        fclean all
	@echo -e "$(GREEN)Cleaned all and rebuilt $(NAME) and $(LIB)!$(END_COLOR)"

.PHONY:    all clean fclean re