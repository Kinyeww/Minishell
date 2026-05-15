/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:24:26 by syee              #+#    #+#             */
/*   Updated: 2026/05/15 14:40:42 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"
#include <stdlib.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && big[i + j] && little[j]
				&& (i + j) < len)
				j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
			j = 0;
		}
		i++;
	}
	return (NULL);
}
