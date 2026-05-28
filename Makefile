NAME = minishell
CFLAGS = -Wall -Wextra -lreadline 
IFLAGS = -Iincludes -Isources

# Source files for export.c testing
CORE = sources/main.c

BUILTINS = sources/execution/Built_ins/export.c\
		   sources/execution/Built_ins/unset.c\
		   sources/execution/Built_ins/env.c\
		   sources/execution/Built_ins/pwd.c\
		   sources/execution/Built_ins/echo.c\
		   sources/execution/Built_ins/cd.c\
		   #sources/execution/Built_ins/exit.c\

ENVP_UTILS = sources/execution/envp_list_utils.c/list_add_back.c\
		   sources/execution/envp_list_utils.c/list_bubble_sort.c\
		   sources/execution/envp_list_utils.c/list_clean.c\
		   sources/execution/envp_list_utils.c/print_list.c\

LIBFT_UTILS = sources/libft_utils/ft_isalnum.c\
		    sources/libft_utils/ft_strchr.c\
		    sources/libft_utils/ft_strcmp.c\
		    sources/libft_utils/ft_strdup.c\
		    sources/libft_utils/ft_strlen.c\
		    sources/libft_utils/ft_strndup.c\
			sources/libft_utils/ft_putstr_fd.c\
			sources/libft_utils/ft_putnbr_fd.c\
			sources/libft_utils/ft_isalpha.c\
			sources/libft_utils/ft_strjoin.c\
			sources/libft_utils/ft_itoa.c\
			sources/libft_utils/ft_substr.c\
			sources/libft_utils/ft_strncmp.c\

EXECUTION = sources/execution/execute.c\
			sources/execution/handle_built_ins.c\

PARSING = sources/parsing/tokenising.c\
		  sources/parsing/parsing.c\
		  sources/parsing/expansion.c\
		  sources/parsing/parsing_utils.c\
		  sources/parsing/init_cmd.c\
		  sources/parsing/free_parsing.c\
		  sources/parsing/heredoc.c\

SRCS = $(CORE) $(BUILTINS) $(ENVP_UTILS) $(LIBFT_UTILS) $(PARSING) #$(EXECUTION)
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
