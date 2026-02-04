#include "minishell.h"
#include "parsing.h"
#include <stdbool.h>
#include <stdlib.h>

static int	ft_counter(const char *s, char c);
static char*	ft_getstr(const char *s, int word_pos, int word_size);
static int	is_split(const char *s, char c, char **str, size_t *filled);

char	*tokenising(char *str)
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
			j = 0;
		}
		else if (str[j] == "'")
			singleq = 1;
		else if (str[j] == '"')
			doubleq = 1;
		else
			tokens->token[i][j] = str[j];
		j++;
	}
	return (true);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	filled;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (ft_counter(s, c) + 1));
	if (!str)
		return (NULL);
	filled = 0;
	if (!is_split(s, c, str, &filled))
	{
		while (filled > 0)
			free(str[--filled]);
		free(str);
		return (NULL);
	}
	return (str);
}

static int	ft_counter(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char*	ft_getstr(const char *s, int word_pos, int word_size)
{
	int		i;
	char*	str;

	i = 0;
	str = malloc(word_size + 1);
	while (i < word_size)
	{
		str[i] = s[word_pos + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	is_split(const char *s, char c, char **str, size_t *filled)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j])
		{
			len = 0;
			while (s[j + len] && s[j + len] != c)
				len++;
			str[i] = ft_getstr(s, j, len);
			if (!str[i])
				return (0);
			(*filled)++;
			i++;
			j += len;
		}
	}
	str[i] = NULL;
	return (1);
}
