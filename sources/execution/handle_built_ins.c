/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:51:13 by syee              #+#    #+#             */
/*   Updated: 2026/05/24 20:18:22 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int built_ins(char **argv, t_data *data) 
{
	int status;
	
	status = 0;
	if (ft_strcmp(argv[0], "echo") == 0)
		status = echo(argv, data);
	else if (ft_strcmp ("cd", argv[0]) == 0)
		status = cd(argv, data);
	else if (ft_strcmp ("pwd", argv[0]) == 0)
		status = pwd(argv, data);
	else if (ft_strcmp ("export", argv[0]) == 0)
		status = export(argv, data);
	else if (ft_strcmp ("unset", argv[0]) == 0)
		status = unset(argv, data);
	else if (ft_strcmp ("env", argv[0]) == 0)
		status = env(argv, data);
	else if (ft_strcmp ("exit", argv[0]) == 0)
		status = built_in_exit(argv, data);
	else
		return (-1);

	return (status);
}

//i create a list of built_ins and check string by string
int check_built_in(char *argv1)
{
	char **built_ins;
	
}