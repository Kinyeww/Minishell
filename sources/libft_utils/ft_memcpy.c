/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:48:26 by syee              #+#    #+#             */
/*   Updated: 2026/05/14 22:31:28 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tempsrc;
	unsigned char	*tempdest;

	tempdest = (unsigned char *) dest;
	tempsrc = (unsigned char *) src;
	if (!tempsrc && !tempdest)
		return (dest);
	while (n-- > 0)
		*(tempdest++) = *(tempsrc++);
	return (dest);
}