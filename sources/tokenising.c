#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include <stdbool.h>
#include <stdlib.h>

static int	get_token_size(char *line);

int	parsing(char *str)
{
	t_token *tokens;
	int	size;

	size = get_token_size(str);
	printf("token size = %d\n", size);
	// tokens = malloc(sizeof(t_token) * size);
	// tokens = tokenising(str, tokens);
	// if (!tokens)
	// 	return (false);
	return (1);
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

static int	get_token_size(char *line)
{
	int	i;
	int	word;
	int	s_quote;
	int	d_quote;
	int	intoken;

	i = 0;
	word = 0;
	intoken = 0;
	s_quote = 0;
	d_quote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (line[i] == '"' && !s_quote)
			d_quote = !d_quote;
		if (line[i] != ' ' || s_quote || d_quote)
		{
			if (!intoken)
			{
				word++;
				intoken = 1;
			}
		}
		else
			intoken = 0;
		i++;
	}
	return (word);
}
