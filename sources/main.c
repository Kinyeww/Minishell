#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av)
{
	t_token *tokens;
	char	*line;

	tokens = malloc(sizeof(t_token));
	while (line = readline("YEESHUNQI GAYYYY$  "))
	{
		// if (tokenising(line, tokens) == false)
		// 	return (1);
		printf("access denied, ur not aura enough to use our shell.\n", line);
		free(line);
	}
	return (0);
}