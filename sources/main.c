#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_token *tokens;
	char	*line;

	(void) ac;
	(void) av;
	(void) envp;
	while (line = readline("YEESHUNQI GAYYYY$  "))
	{
		// if (parsing(line))
		printf("access denied, ur not aura enough to use our shell.\n");
		printf("%d %d %d %d %d", WORD, PIPE, APPEND, REDIR_IN, REDIR_OUT);
		free(line);
	}
	return (0);
}