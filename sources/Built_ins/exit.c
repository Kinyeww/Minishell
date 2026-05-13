/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 23:42:33 by syee              #+#    #+#             */
/*   Updated: 2026/05/13 19:33:13 by syee             ###   ########.fr       */
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
 
*/

int	exit(char **argv, t_data *data)
{
	if (!(*(argv++)))
		return (0);
	
	data->exit_code = true;
	return (0);
}