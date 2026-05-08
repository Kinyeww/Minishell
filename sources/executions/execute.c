/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:13:51 by syee              #+#    #+#             */
/*   Updated: 2026/05/08 20:11:36 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_ast(t_ast *node)
{
	if (node->type == NODE_COMMAND)
        execute_command(node->cmd);
    else if (node->type == NODE_PIPE)
        execute_pipe(node);
}

//traverse_ast () //go to all the left first then rebound to the right 
// 
void execute_comand()
{
	//traverse the ast recursively with the split commands 
	//check for built in parser and so on 
	//handle the errors within each commands ? 
		
}