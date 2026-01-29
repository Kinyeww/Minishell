#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_token *tokens;

	tokens = malloc(sizeof(t_token));
	if (!parsing_check (ac, av, tokens))
	{
		printf("invalid arg\n");
		return (1);
	}
	printf("\n%s\n", tokens->token); //testing
	// if (!tokenise)
	// 	return (1);
	return (0);
}