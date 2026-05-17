/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:23:58 by syee              #+#    #+#             */
/*   Updated: 2026/05/17 14:09:56 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newword;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	newword = (char *)malloc(len + 1);
	while (s1[j])
		newword[i++] = s1[j++];
	j = 0;
	while (s2[j])
		newword[i++] = s2[j++];
	newword[i] = '\0';
	return (newword);
}
