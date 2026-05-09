#include <stdlib.h>

int	ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *str);
char *ft_strdup(char *string);
char *ft_strchr(char *string, char c);
char *ft_strndup(char *string , int size);

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2) //in reality it will be undefined behaviour 
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	else
	{
		while (str[i])
			i++;
	}
	return (i);
}

char *ft_strdup(char *string)
{
	int i; 
	char *str;

	if (!string)
        return (NULL);
	i = 0;
	while (string[i])
		i++;
	str = malloc(i + 1);
	i = 0;
	while (string[i])
	{
		str[i] = string[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strchr(char *string, char c)
{
	int i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (string + i);
	}
	return (NULL);
}


char *ft_strndup(char *string , int size)
{
	int		i;
	char	*return_str;

	i = 0;
	if (!string)
		return (NULL);
	return_str = malloc(size + 1);
	while (string[i] != '\0')
	{
		return_str[i] = string[i];
		i++;
	}
	return (return_str);
}