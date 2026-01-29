#include "../includes/parsing.h"
#include <stdio.h>
#include <stdlib.h>

int	parsing_check(int ac, char **av, t_token *tokens)
{
	int	j;
	int	a = 0;

	if (!av[1])
		return (0);
	while (av[1][a])
		a++;
	tokens->token = malloc(sizeof(char) * (a + 1));
	j = 0;
	while (av[1][j])
	{
		tokens->token[j] = av[1][j];
		j++;
	}
	tokens->token[j] = 0;
	printf("%d", ac);
	return (1);
}