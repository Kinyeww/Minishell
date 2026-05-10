#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int		get_token_length(char *line, int tokennum);
static size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void			print_list_size(t_token *tokens);

/*what this does is return a tokenised linked list for example like hello world = hello->world*/

t_token	*tokenising(char *line) //extra 4 lines
{
	t_token	*new_tokens;
	t_token	*head;
	t_token	*last;
	int		len;
	int		i;

	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		len = get_token_length(line, i);
		if (len == 0)
			break ;
		new_tokens = malloc (sizeof(t_token));
		new_tokens->content = malloc (sizeof(char) * (len + 1));
		while (line[i] && line[i] == ' ')
			i++;
		ft_strlcpy(new_tokens->content, line + i, len + 1);
		if (!head)
			head = new_tokens;
		else
			last->next = new_tokens;
		last = new_tokens;
		i += len;
	}
	last->next = NULL;
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
	t_tokenising	s;
	int				i;
	// int				word;

	s.i = index;
	s.one_q = 0;
	s.two_q = 0;
	i = 0;
	while (line[i + s.i] && line[i + s.i] == ' ')
		s.i++;
	while (line[i + s.i] && (line[i + s.i] != ' ' || s.one_q || s.two_q))
	{
		if (line[i + s.i] == '\'' && !s.two_q)
			s.one_q = !s.one_q;
		else if (line[i + s.i] == '"' && !s.one_q)
			s.two_q = !s.two_q;
		i++;
	}
	return (i);
}
