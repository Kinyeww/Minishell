#include "minishell.h"

t_token	*new_token(char *start, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof(char) * (len + 1));
	if (!new->content)
		return (NULL);
	ft_strlcpy(new->content, start, len + 1);
	new->type = -1;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
 one thing to note about the split token is that
 whenever we see space or operator, we split it into tokens
 however we do not want to split it when it is inside the quotes
 because it is counted as string literal
 that means the space inside quotes shouldn't be splitted
*/

int	get_token_length(char *line, int index)
{
	int				one_q;
	int				two_q;
	int				i;

	i = 0;
	one_q = 0;
	two_q = 0;
	while (line[index + i])
	{
		if (line[index + i] == '\'' && !two_q)
			one_q = !one_q;
		else if (line[index + i] == '"' && !one_q)
			two_q = !two_q;
		else if (!one_q && !two_q && line[index + i] == ' ')
			break ;
		else if (!one_q && !two_q && is_operator(line[index + i]))
			break ;
		i++;
	}
	if (one_q || two_q)
		return (-1);
	return (i);
}

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	get_operator_len(char *line, int i)
{
	if ((line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '<' && line[i + 1] == '<'))
		return (2);
	return (1);
}
