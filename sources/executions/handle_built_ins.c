/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:51:13 by syee              #+#    #+#             */
/*   Updated: 2026/05/11 21:04:00 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

//argv[0] is the command itself, argv are passed entirely to view its contents
int built_ins(char **argv, t_data *data) 
{
	int status;
	
	if (ft_strcmp(argv[0], "echo") == 0)
		status = echo(argv);
	else if (ft_strcmp ("cd", argv[0]))
		status = cd(argv, data->envp_list);
	else if (ft_strcmp ("pwd", argv[0]))
		status = pwd(argv);
	else if (ft_strcmp ("export", argv[0]))
		status = export(argv, data);
	else if (ft_strcmp ("unset", argv[0]))
		status = unset(argv);
	else if (ft_strcmp ("env", argv[0]))
		status = env(argv);
	else if (ft_strcmp ("exit", argv[0]))
		exit(argv);
	else
		return (1);

	return (0); 
}
