/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:03:30 by syee              #+#    #+#             */
/*   Updated: 2026/05/31 20:06:52 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
/*
- this funciton does not remove trailing white spaces, or 0 before the actual 
values
- this function will segfault if the received value is larger than LONG_MAX / LONG_MIN
*/
long ft_atol(char *str)
{
	bool	neg;
	long	return_val;

	if (str[0] == '-')
	{
		neg = 1;
		str++;
	}
	if (str[0] == '0' || (str[0] == '-' && str[1] == '0'))
		return (0);
	return_val = 0;
	while (*str)
	{
		return_val = (*str - '0') + (return_val * 10);
		str++;
	}
	if (neg == 1)
		return (return_val * -1);
	return (return_val);
}