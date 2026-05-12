/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:38:31 by syee              #+#    #+#             */
/*   Updated: 2026/05/12 23:40:30 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv, t_data *data)
{
	int		i;
	bool	newline_flag;
	
	(void)data;
	i = 1;
	newline_flag = 1;
	while (ft_strcmp(argv[i], "-n") == 0)
		i++;
	if (i > 1)
		newline_flag = 0;
	while (argv[i] != NULL)
	{
		write (1, argv[i], ft_strlen(argv[i]));
		write (1, " ", 1);
		i++;
	}
	if (newline_flag == 1)
		write(1, "\n", 1);
	return (0);
}
