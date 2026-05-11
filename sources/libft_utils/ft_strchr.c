/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 07:59:16 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 08:06:32 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_strchr(char *string, char c)
{
	int i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == c)
			return (string + i);
		i++;
	}
	return (NULL);
}