NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -lreadline 
IFLAGS = -Iincludes -Isources

# Source files for export.c testing
CORE = sources/main.c\
	   #sources/tokenising.c\
	   #sources/parsing.c\

BUILTINS = sources/Built_ins/export.c\
		   sources/Built_ins/unset.c\
		   sources/Built_ins/env.c\
		   #sources/Built_ins/echo.c\
		   #sources/Built_ins/exit.c\
		   #sources/Built_ins/pwd.c\
		   #sources/Built_ins/cd.c\

ENVP_UTILS = sources/envp_list_utils.c/list_add_back.c\
		   sources/envp_list_utils.c/list_bubble_sort.c\
		   sources/envp_list_utils.c/list_clean.c\
		   sources/envp_list_utils.c/print_list.c\

LIBFT_UTILS = sources/libft_utils/ft_isalnum.c\
		    sources/libft_utils/ft_strchr.c\
		    sources/libft_utils/ft_strcmp.c\
		    sources/libft_utils/ft_strdup.c\
		    sources/libft_utils/ft_strlen.c\
		    sources/libft_utils/ft_strndup.c\
			sources/libft_utils/ft_putstr_fd.c\
			sources/libft_utils/ft_putnbr_fd.c\
			sources/libft_utils/ft_isalpha.c\

EXECUTION = sources/executions/execute.c\
			sources/executions/handle_built_ins.c\

SRCS = $(CORE) $(BUILTINS) $(ENVP_UTILS) $(LIBFT_UTILS) #$(EXECUTION)
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(IFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

me: re
	rm -f $(OBJS)

.PHONY: all clean fclean re me
