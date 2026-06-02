/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:02:18 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 18:18:02 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	writenbr(long long n, int fd)
{
	char	c;

	if (n != 0)
	{
		writenbr(n / 10, fd);
		c = (n % 10) + '0';
		write (fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	x;

	x = (long long)n;
	if (n < 0)
	{
		write (fd, "-", 1);
		x = -1 * x;
	}
	if (n == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	writenbr (x, fd);
}
