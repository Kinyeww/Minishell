#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int		get_token_length(char *line, int tokennum);
static size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void			print_list_size(t_token *tokens);
t_token			*new_token(char *start, int len);
static int		is_operator(char c);
static int		get_operator_len(char *line, int i);


/*what this does is return a tokenised linked list for example like hello world = hello->world*/

t_token	*tokenising(char *line)
{
	t_token	*new;
	t_token	*head;
	t_token	*last;
	int		len;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (is_operator(line[i]))
			len = get_operator_len(line, i);
		else
			len = get_token_length(line, i);
		if (len < 0)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
			free_tokens(head);
			return (NULL);
		}
		if (len == 0)
			break ;
		new = new_token(line + i, len);
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i += len;
	}
	print_list_size(head);
	return (head);
}

void	print_list_size(t_token *tokens)
{
	int	i = 0;

	while (tokens)
	{
		printf("token[%d] =%s\n", i, tokens->content);
		tokens = tokens->next;
		i++;
	}
	printf("token count = %d\n", i);
}

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

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (size == 0 || i == 0)
		return (i);
	j = 0;
	while (j < size - 1 && src[j])
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (i);
}

/*
 one thing to note about the split token is that
 whenever we see space, we split it into tokens
 however we do not want to split it when it is inside the quotes
 because it is counted as string literal
 that means the space inside quotes shouldn't be splitted
*/

static int	get_token_length(char *line, int index)
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

static int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

static int	get_operator_len(char *line, int i)
{
	if ((line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '<' && line[i + 1] == '<'))
		return (2);
	return (1);
}
