/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 07:56:43 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 08:06:57 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char *ft_strndup(char *string , int size)
{
	int		i;
	char	*return_str;

	i = 0;
	if (!string)
		return (NULL);
	return_str = malloc(size + 1);
	while (i <size && string[i] != '\0')
	{
		return_str[i] = string[i];
		i++;
	}
	return_str[i] = '\0';
	return (return_str);
}