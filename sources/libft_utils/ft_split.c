/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 20:15:24 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 18:18:08 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft_utils.h"

static void	freeptr(char ***arradd, int index)
{
	char	**tmp;

	tmp = *arradd;
	while (index >= 0)
	{
		free(tmp[index]);
		index--;
	}
	free(tmp);
	tmp = NULL;
}

static size_t	wordcount(const char *s, char c)
{
	size_t		word;
	int			i;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			word++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (word);
}

static char	**allocateword(char *words, char *worde, char **arr, int index)
{
	int		len;

	len = worde - words;
	arr[index] = (char *)malloc(len + 1);
	if (!arr[index])
	{
		freeptr(&arr, index - 1);
		return (NULL);
	}
	ft_memcpy(arr[index], words, len);
	arr[index][len] = '\0';
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	*pointerstart;
	int		index;
	int		i;

	arr = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (!arr)
		return (NULL);
	index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			pointerstart = (char *)(s + i);
			while (s[i] && s[i] != c)
				i++;
			if (!allocateword(pointerstart, (char *)(s + i), arr, index++))
				return (NULL);
		}
		while (s[i] && s[i] == c)
			i++;
	}
	arr[index] = NULL;
	return (arr);
}
