# **************************************************************************** #
# COLORS

GREEN        := \033[0;92m
YELLOW        := \033[0;93m
BLUE        := \033[0;94m
END_COLOR    := \033[0;39m

# **************************************************************************** #
# VARIABLES

SRCS    =    src/handle.c \
            src/exec.c \
            src/exec_run.c \
            src/exec_utils.c \
            src/command.c \
            src/parser.c \
            src/parser_utils.c \
            src/redir.c \
            src/redir_list.c \
            src/shell.c \
            src/shell_utils.c \
            src/syntax.c \
			src/heredoc.c \
			src/heredoc_expand.c \
            src/token.c \
			src/env_setup.c \
			src/env_split.c \
			src/free_utils.c \
			src/env_utils.c \
			src/utils_path.c \
			src/expand.c \
			src/expand_utils.c \
			src/output_utils.c \
			src/builtins/ft_cd.c \
			src/builtins/ft_cd_utils.c \
			src/builtins/ft_echo.c \
			src/builtins/ft_env.c \
			src/builtins/ft_exit.c \
			src/builtins/ft_export.c \
			src/builtins/ft_export_utils.c \
			src/builtins/ft_pwd.c \
			src/builtins/ft_unset.c
OBJ        =    ${SRCS:.c=.o}
HEADER    =   include/minishell.h
NAME    =    minishell
LIB        =    lib/libft-pilagach/libft.a
CC        =    cc
CFLAGS    =    -Wall -Wextra -Werror -Iinclude -Ilib -g

# **************************************************************************** #
# RULES

%.o:    %.c
	@${CC} ${CFLAGS} -c -g $< -o $@
	@echo -e "$(BLUE)Compiling $<...$(END_COLOR)"

$(NAME):    ${OBJ} Makefile
	@make --no-print-directory -C lib/libft-pilagach all
	@make --no-print-directory -C lib/libft-pilagach clean
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) -l readline
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