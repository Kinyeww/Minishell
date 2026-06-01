/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:08:14 by syee              #+#    #+#             */
/*   Updated: 2026/05/14 20:22:39 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

/*
will break if a stupidly large value is placed
*/
int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	result;

	minus = 0;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus++;
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (minus % 2 != 0)
		result = -result;
	return (result);
}
