NAME = minishell
CC = gcc
CFLAGS =
SRCS =	minishell.c \
		srcs/signal.c \
		utils/get_next_line/get_next_line.c \
		utils/get_next_line/get_next_line_utils.c \
		utils/file.c \
		utils/little_func.c \
		utils/error_manager.c \
		srcs/echo.c \
		srcs/exit.c \
		srcs/pwd.c \
		utils/ft_split.c \
		utils/check_cmd.c

#utils/file.c \#

INC	= -I /Users/$$USER/.brew/opt/readline/include

LIB	= -lreadline -L/Users/$$USER/.brew/opt/readline/lib

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} ${INC} -g3 -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

debug: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LIB) -o $(NAME)

all: $(NAME)

bonus: all

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
