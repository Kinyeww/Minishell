NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
LDLIBS = -lreadline
IFLAGS = -Iincludes -Isources

GREEN = \033[0;32m
RESET = \033[0m
BAR_WIDTH = 30

BUILTINS = sources/execution/Built_ins/export.c\
		   sources/execution/Built_ins/export_err.c\
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
              sources/libft_utils/ft_memcpy.c\
              sources/libft_utils/ft_atol.c\
			  sources/libft_utils/ft_itoa.c\
			  sources/libft_utils/ft_strncmp.c\
			  sources/libft_utils/ft_substr.c\
			  sources/libft_utils/ft_strlcpy.c\

EXECUTION = sources/execution/execute_binary_built-in/execute_binary.c\
            sources/execution/execute_binary_built-in/execute_binary_helper.c\
            sources/execution/execute_binary_built-in/execute_built_ins.c\
            sources/execution/pipes/execute_pipes.c\
            sources/execution/redirection/execute_redir.c\
			sources/execution/redirection/execute_redir_helper.c\
			sources/execution/redirection/execute_redir_setup.c\

PARSING = sources/parsing/tokenising.c\
          sources/parsing/parsing.c\
          sources/parsing/expansion.c\
		  sources/parsing/expansion_utils.c\
          sources/parsing/parsing_utils.c\
          sources/parsing/init_cmd.c\
          sources/parsing/free_parsing.c\
          sources/parsing/heredoc.c\
		  sources/parsing/heredoc_utils.c\
		  sources/parsing/heredoc_expand.c\
		  sources/parsing/tokenising_utils.c

SRCS = sources/main.c\
       sources/execution/signals/signals.c\
	   sources/execution/signals/signals_exe.c\
	   sources/main_setup_cleanup.c\
	   sources/main_helper.c\
       $(BUILTINS)\
       $(ENVP_UTILS)\
       $(LIBFT_UTILS)\
       $(EXECUTION)\
       $(PARSING)

OBJS = $(SRCS:.c=.o)

TOTAL := $(words $(SRCS))
COUNT := 0

define progress_bar
$(eval COUNT := $(shell echo $$(($(COUNT) + 1))))
@percent=$$(( $(COUNT) * 100 / $(TOTAL) )); \
filled=$$(( percent * $(BAR_WIDTH) / 100 )); \
empty=$$(( $(BAR_WIDTH) - filled )); \
bar=""; \
i=0; \
while [ $$i -lt $$filled ]; do \
	bar="$${bar}█"; \
	i=$$((i + 1)); \
done; \
spaces=""; \
i=0; \
while [ $$i -lt $$empty ]; do \
	spaces="$${spaces} "; \
	i=$$((i + 1)); \
done; \
printf "\r$(GREEN)Compiling [$$bar$$spaces] %3d%%$(RESET)" $$percent
endef

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(IFLAGS) -o $(NAME) $(LDLIBS)
	@printf "\n$(GREEN)Compilation complete!$(RESET)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	$(call progress_bar)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

me: re
	@rm -f $(OBJS)

.PHONY: all clean fclean re
