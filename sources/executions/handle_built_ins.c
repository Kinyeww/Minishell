/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_built_ins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 19:51:13 by syee              #+#    #+#             */
/*   Updated: 2026/05/08 19:51:13 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*- echo with option -n
 cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options */
#include "ast.h"
#include <stdlib.h>


/*
char **x <- addr of the str
if x[i] = "xx", then will manipulate the value inside 

*/

/*
-takes in the command/ argv from the ast
- returns -1 on error and returns 0 on success, returns 1 if its not a built in  ? , use #define int that file 

//to do : change cmd to argv to align with the ast and the contents within the funcitons
-*/
int built_ins(char **cmd, t_data *data) 
{
	int status;
	
	if (ft_strcmp ("echo", cmd[0]))
		status = echo(cmd);
	else if (ft_strcmp ("cd", cmd[0]))
		status = cd(cmd, data->envp);
	else if (ft_strcmp ("pwd", cmd[0]))
		status = pwd(cmd);
	else if (ft_strcmp ("export", cmd[0]))
		status = export(cmd);
	else if (ft_strcmp ("unset", cmd[0]))
		status = unset(cmd);
	else if (ft_strcmp ("env", cmd[0]))
		status = env(cmd);
	else if (ft_strcmp ("exit", cmd[0]))
		status = exit(cmd);
	else
		return (1);

	return (0); 
}

/*
order should be : 
- check for built ins then check for external 
 
*/