#include "../includes/minishell.h"
#include "../includes/parsing.h"
#include "../includes/tokenising.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int		get_token_size(char *line);
static int		get_word_count(char *line, int intoken, int singleq, int doubleq);
static int		get_token_length(char *line, int tokennum);
static void		get_token_length_utils(char *line, int *i, int *word, int intoken);
static size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void			print_list_size(t_token *tokens);

int	parsing(char *line)
{
	t_token *new_tokens;
	t_token *head;
	t_token *last;
	int	size;
	int	len;
	int	i;

	size = get_token_size(line);
	printf("\ntoken size = %d\n", size);
	i = 0;
	head = NULL;
	last = NULL;
	while (line[i])
	{
		len = get_token_length(line, i);
		printf("token length = %d\n", len);
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
	return (1);
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
	if (size == 0)
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

static int	get_token_length(char *line, int index)
{
	t_tokenising	s;
	int				i;
	int				word;

	s.i = index;
	s.singleq = 0;
	s.doubleq = 0;
	i = 0;
	{
		while (line[i + s.i] && line[i + s.i] == ' ')
			s.i++;
		while (line[i + s.i] && (line[i + s.i] != ' ' || s.singleq || s.doubleq))
		{
			if (line[i + s.i] == '\'' && !s.doubleq)
				s.singleq = !s.singleq;
			else if (line[i + s.i] == '"' && !s.singleq)
				s.doubleq = !s.doubleq;
			i++;
		}
		return (i);
	}
}

static void get_token_length_utils(char *line, int *i, int *word, int tokennum)
{
	t_tokenising	state;

	state.singleq = 0;
	state.doubleq = 0;
	state.intoken = 0;
	while (line[*i] && *word < tokennum)
	{
		if (line[*i] == '\'' && !state.doubleq)
			state.singleq = !state.singleq;
		else if (line[*i] == '"' && !state.singleq)
			state.doubleq = !state.doubleq;
		if (line[*i] != ' ' || state.singleq || state.doubleq)
		{
			if (!state.intoken)
			{
				(*word)++;
				state.intoken = 1;
			}
		}
		else
			state.intoken = 0;
		(*i)++;
	}
}

static int	get_token_size(char *line)
{
	int	word;
	int	s_quote;
	int	d_quote;
	int	intoken;

	intoken = 0;
	s_quote = 0;
	d_quote = 0;
	word = get_word_count(line, intoken, s_quote, d_quote);
	return (word);
}

static int get_word_count(char *line, int intoken, int singleq, int doubleq)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !doubleq)
			singleq = !singleq;
		else if (line[i] == '"' && !singleq)
			doubleq = !doubleq;
		if (line[i] != ' ' || singleq || doubleq)
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