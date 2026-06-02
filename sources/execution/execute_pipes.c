/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:05:35 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 21:15:47 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

/*
dup2(old, new) <- new is now new = old
dup2(fd, 1); // stdout (1) now goes to file , 1 will point to where fd is 

pipefd[1] ---> pipe ---> pipefd[0]
   write                    read
*/
int	traverse_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int 		pipefd[2];
	int			prev_cmd_read_end;
	pid_t		pid;
	int			child_process_status;
	int			last_child_pid;
	int			last_child_status;
	
	set_signal_exec_parent();
	if (cmd->next == NULL)
	{
		/*
		if it is a singular process, just execute the singular command 
		and return() , then update the exit code 
		*/
		return (execute_cmd(cmd, data));
	}
	prev_cmd_read_end = -1;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);//for each command, create thier own pipes
		pid = fork();
		if (pid == 0)//if child proceess
		{		
			set_signal_exec_child();	
			if (prev_cmd_read_end != -1) //if there was a prev cmd
			{
				dup2(prev_cmd_read_end, STDIN_FILENO);
				close (prev_cmd_read_end);
			}
			if (cmd->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close (pipefd[1]);
				close (pipefd[0]);
			}
			exit(execute_cmd(cmd, data)); //execute_cmd will return a code used to update
		}
		else if (pid > 0)
		{
			set_signal_exec_parent();
			close(pipefd[1]); //its not writing to anywhere
			if (cmd->next)
			{
				if (prev_cmd_read_end != -1)
    				close(prev_cmd_read_end);
				prev_cmd_read_end = pipefd[0];
			}
			else
			{	
				close (prev_cmd_read_end);
				close(pipefd[0]);
				last_child_pid = pid;
			}
			cmd = cmd->next;
		}
	}
	
	while ((pid = waitpid(-1, &child_process_status, 0)) > 0) //returns -1 upon all child returning
	{
		if (last_child_pid == pid)
			last_child_status = child_process_status;
	}	
	//set_signal_prompt(); //to refresh the signal's assignment 
	
	//i dont think theres a need for this because this signal status is based on the child 
	if (WIFSIGNALED(last_child_status))
		return (128 + WTERMSIG(last_child_status));
	else if (WIFEXITED(last_child_status))  //if the child exited normally
		return (WEXITSTATUS(last_child_status));
	else
		return (1); //just to silence compilar warnings
}


