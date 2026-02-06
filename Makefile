NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -lreadline

PARSING = sources/main.c\
# 		  sources/parsing.c\
# 		  sources/

# EXECUTION = sources/

SRCS = $(PARSING) $(EXECUTION)
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

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