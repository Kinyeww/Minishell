/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_ins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:51:13 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 15:30:02 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

//this is a slight issue because, the i is based on whats traversed
int execute_built_ins(char **argv, t_data *data)
{
	int status;
	
	status = 0;
	if (ft_strcmp("echo", *argv) == 0)
		status = echo(argv, data);
	else if (ft_strcmp ("cd", *argv) == 0)
		status = cd(argv, data);
	else if (ft_strcmp ("pwd", *argv) == 0)
		status = pwd(argv, data);
	else if (ft_strcmp ("export", *argv) == 0)
		status = export(argv, data);
	else if (ft_strcmp ("unset", *argv) == 0)
		status = unset(argv, data);
	else if (ft_strcmp ("env", *argv) == 0)
		status = env(argv, data);
	else if (ft_strcmp ("exit", *argv) == 0)
		status = built_in_exit(argv, data);

	return (status);
}