NAME = minishell
CC = cc
CFLAGS = # -Wall -Wextra
LDLIBS = -lreadline
IFLAGS = -Iincludes -Isources

BUILTINS = sources/execution/Built_ins/export.c\
           sources/execution/Built_ins/unset.c\
           sources/execution/Built_ins/env.c\
           sources/execution/Built_ins/pwd.c\
           sources/execution/Built_ins/echo.c\
           sources/execution/Built_ins/cd.c\
           sources/execution/Built_ins/exit.c

ENVP_UTILS = sources/execution/envp_list_utils.c/create_envp_list.c\
                 sources/execution/envp_list_utils.c/list_add_back.c\
                 sources/execution/envp_list_utils.c/list_bubble_sort.c\
                 sources/execution/envp_list_utils.c/list_clean.c\
                 sources/execution/envp_list_utils.c/print_list.c\

LIBFT_UTILS = sources/libft_utils/ft_isalnum.c\
              sources/libft_utils/ft_isalpha.c\
              sources/libft_utils/ft_strchr.c\
              sources/libft_utils/ft_strcmp.c\
              sources/libft_utils/ft_strdup.c\
              sources/libft_utils/ft_strlen.c\
              sources/libft_utils/ft_strndup.c\
              sources/libft_utils/ft_putstr_fd.c\
              sources/libft_utils/ft_putnbr_fd.c\
              sources/libft_utils/ft_strjoin.c\
              sources/libft_utils/ft_atoi.c\
              sources/libft_utils/ft_strnstr.c\
              sources/libft_utils/ft_split.c\
              sources/libft_utils/ft_memcpy.c

EXECUTION = sources/execution/execute_binary.c\
            sources/execution/execute_binary_helper.c\
            sources/execution/execute_built_ins.c\
            sources/execution/execute_pipes.c\
            sources/execution/execute_redir.c

PARSING = sources/parsing/tokenising.c\
          sources/parsing/expansion.c\
          sources/parsing/parsing/parsing.c\
          sources/parsing/parsing/parsing_utils.c\
          sources/parsing/parsing/parsing_addrc.c

SRCS = sources/temp_test_case_files/main_test_execution.c\
       sources/temp_test_case_files/test_cases.c\
       $(BUILTINS)\
       $(ENVP_UTILS)\
       $(LIBFT_UTILS)\
       $(EXECUTION)\
       $(PARSING)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(IFLAGS) -o $(NAME) $(LDLIBS)

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re