NAME = minishell
CC = gcc
CFLAGS =
SRCS =	minishell.c \
		srcs/signal.c \
		utils/get_next_line/get_next_line.c \
		utils/get_next_line/get_next_line_utils.c \
		utils/file.c \
		utils/little_func.c
INC	= -ledit

OBJS = ${SRCS:.c=.o}

.c.o:
	${CC} ${CFLAGS} -g3 -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC)

all: $(NAME)

bonus: all

clean:
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
