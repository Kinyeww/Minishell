/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:05:35 by syee              #+#    #+#             */
/*   Updated: 2026/05/29 07:49:06 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h> //for the stdout or stdin

/*
dup2(old, new) <- new is now new = old
dup2(fd, 1); // stdout (1) now goes to file , 1 will point to where fd is 

pipefd[1] ---> pipe ---> pipefd[0]
   write                    read
*/

void	traverse_pipe_cmd(t_cmd *cmd, t_data *data)
{
	int 		pipefd[2];
	int			prev_cmd_read_end;
	pid_t		pid;
	int			child_process_status;
	int			last_child_pid;
	
	if (cmd->next == NULL)
	{
		/*
		if it is a singular process, just execute the singular command 
		and return() , then update the exit code 
		*/
		execute_cmd(cmd, data);	
	}
	prev_cmd_read_end = data->fd_copy[0];
	while (cmd)
	{
		pipe(pipefd);//for each command, create thier own pipes
		pid = fork();
		if (pid == 0)//if child proceess
		{			
			if (prev_cmd_read_end != 0)
			{
				dup2(prev_cmd_read_end, STDIN_FILENO);
				close (prev_cmd_read_end);
			}
			if (cmd->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close (pipefd[1]);
			close (pipefd[0]);
			exit(execute_cmd(cmd->argv[0], data)); //executecmd will return a code used to update
		}
		else if (pid > 0)
		{
			close(pipefd[1]);
			if (cmd->next)
				prev_cmd_read_end = pipefd[0];
			else
			{
				close(pipefd[0]);
				last_child_pid = pid;
			}
			cmd = cmd->next;
		}
	}
	waitpid(-1, &child_process_status, 0);
	
	if (WIFSIGNALED(child_status)) //if the child exited via termination
		return (128 + WTERMSIG(child_status));
	else if (WIFEXITED(child_status))  //if the child exited normally
		return (WEXITSTATUS(child_status));
	else
		return (1);

	//wait for the child proccesses to return;
}

//rmbr to close later on?
void	create_stdin_stdout_cpy(t_data *data)
{
	data->fd_copy[0] = dup(STDIN_FILENO);
	data->fd_copy[1] = dup(STDOUT_FILENO);
}

// int	main(void)
// {
// 	t_cmd	cmd1;
// 	t_cmd	cmd2;
// 	t_cmd	cmd3;

// 	char *argv1[] = {"cmd1", NULL};
// 	char *argv2[] = {"cmd2", NULL};
// 	char *argv3[] = {"cmd3", NULL};

// 	cmd1.argv = argv1;
// 	cmd2.argv = argv2;
// 	cmd3.argv = argv3;

// 	cmd1.next = &cmd2;
// 	cmd2.next = &cmd3;
// 	cmd3.next = NULL;

// 	traverse_cmd(&cmd1);

// 	return (0);
// }