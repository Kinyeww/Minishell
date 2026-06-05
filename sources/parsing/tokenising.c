#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void	skip_spaces(char *line, int *i);
int		get_next_token_len(char *line, int i);
t_token	*handle_unclosed_quote(t_token *head);
int		add_token_to_list(t_token **head, t_token **last, char *str, int len);

t_token	*tokenising(char *line)
{
	t_token	*head;
	t_token	*last;
	int		len;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		len = get_next_token_len(line, i);
		if (len < 0)
			return (handle_unclosed_quote(head));
		if (len == 0)
			break ;
		if (!add_token_to_list(&head, &last, line + i, len))
			return (NULL);
		i += len;
	}
	return (head);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	get_next_token_len(char *line, int i)
{
	if (is_operator(line[i]))
		return (get_operator_len(line, i));
	return (get_token_length(line, i));
}

t_token	*handle_unclosed_quote(t_token *head)
{
	ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
	free_tokens(head);
	return (NULL);
}

int	add_token_to_list(t_token **head, t_token **last, char *str, int len)
{
	t_token	*new;

	new = new_token(str, len);
	if (!new)
	{
		free_tokens(*head);
		return (0);
	}
	if (!*head)
		*head = new;
	else
		(*last)->next = new;
	*last = new;
	return (1);
}
