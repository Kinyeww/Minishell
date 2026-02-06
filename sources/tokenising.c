#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdlib.h>

int	parsing(char *str, t_token *tokens)
{
	t_token *tokens;
	int	size;

	size = get_token_size(tokens);
	tokens =
	tokens = tokenising(str, tokens);
	if (!tokens)
		return (false);
	
}

t_token *tokenising(char *str, t_token *tokens)
{
	int	i;
	int	j;
	int	singleq;
	int	doubleq;

	i = 0;
	j = 0;
	singleq = 0;
	doubleq = 0;
	while (str[j])
	{
		if (singleq != 1 && doubleq != 1 && str[j] == ' ') // if its 1 token (seperated by spaces)
		{
			i++;
		}
		else if (str[j] == '\'')
			singleq = 1;
		else if (str[j] == '"')
			doubleq = 1;
		else
		i++;
	}
	return (true);
}
