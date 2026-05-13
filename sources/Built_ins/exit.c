/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:42:33 by syee              #+#    #+#             */
/*   Updated: 2026/05/13 22:08:06 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
when exit is called it :
- flags to quit
- 

arguments to handle : 
- if its a valid number
- if its not a valid argument : quit with 0?
 
in main 
- return with data->exit_code

*/

int	exit(char **argv, t_data *data)
{
	int	i;

	if (argv[1])
	if (!(*(argv++)))
		return (0);
	
	data->exit_code = true;
	printf ("exit\n");
	return (0);
}