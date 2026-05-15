/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:13:51 by syee              #+#    #+#             */
/*   Updated: 2026/05/15 13:04:51 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void traverse_cmd(t_cmd *cmd)
{
	char **argv;
	argv = cmd->argv;
	//first chekc if the cmd is empty
	/*
	if (redir)
	{
		if ()
		else if ()
		else if ()
	}
	*/
}
void execute_cmd(char **argv, t_data *data)
{
	if (built_ins(argv, data) == -1)
		;
	else if (binary(argv, data) == -1)
		;
	else
		;
		
}

/*
passed : echo "hi" > file.txt
argv = "echo", "hi"

*/