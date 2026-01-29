NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra

SRCS = sources/main.c sources/parsing.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

me: re
	rm -f $(OBJS)

.PHONY: all clean fclean re me