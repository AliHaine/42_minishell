# j'ai mis des echo pour la compilemais c pas definitif c juste comme ça fait moin de messages

NAME = minishell

CC = @gcc

CFLAGS =

SRCS =	minishell.c \
		srcs/signal.c \
		utils/get_next_line/get_next_line.c \
		utils/get_next_line/get_next_line_utils.c \
		utils/file.c \
		utils/very_little_func.c \
		utils/little_func.c \
		utils/error_manager.c \
		srcs/echo.c \
		srcs/pwd.c \
		utils/ft_split.c \
		utils/check_cmd.c \
		srcs/env.c \
		srcs/unset.c \
		srcs/export.c \
		srcs/cd.c \
		srcs/pipe_manager.c \
		utils/pipe_utils.c \
		utils/utils.c \
		utils/trime_quotation.c \
		utils/cmds_struct.c \
		utils/utils2.c \
		utils/env_conversion.c \
		srcs/execve.c \
		utils/utils3.c

#utils/file.c \#

INC	= -I /Users/$$USER/.brew/opt/readline/include

LIB	= -lreadline -L/Users/$$USER/.brew/opt/readline/lib

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} ${INC} -g3 -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
	@echo "minshell compiled!"

debug: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LIB) -o $(NAME)

all: $(NAME)

bonus: all

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo "minshell cleaned!"

fclean: clean
	@rm -rf $(NAME)
	@echo "minshell fcleaned!"

re: fclean all

.PHONY: all clean fclean
