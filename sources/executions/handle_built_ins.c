/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:51:13 by syee              #+#    #+#             */
/*   Updated: 2026/05/10 05:23:08 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

//args[0] is the command itself, args are passed entirely to view its contents
int built_ins(char **args, t_data *data) 
{
	int status;
	
	if (ft_strcmp(args[0], "echo") == 0)
		status = echo(args);
	else if (ft_strcmp ("cd", args[0]))
		status = cd(args, data->envp_list);
	else if (ft_strcmp ("pwd", args[0]))
		status = pwd(args);
	else if (ft_strcmp ("export", args[0]))
		status = export(args, data);
	else if (ft_strcmp ("unset", args[0]))
		status = unset(args);
	else if (ft_strcmp ("env", args[0]))
		status = env(args);
	else if (ft_strcmp ("exit", args[0]))
		exit(args);
	else
		return (1);

	return (0); 
}
