/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:05:35 by syee              #+#    #+#             */
/*   Updated: 2026/05/27 02:53:22 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h> //for the stdout or stdin
/*
dup2(old, new) <- new is now new = old
dup2(fd, 1); // stdout (1) now goes to file , 1 will point to where fd is 

pipefd[1] ---> pipe ---> pipefd[0]
   write                    read
*/
/*
how do i test this?
*/

// typedef struct s_redir
// {
// 	t_token_type	redir_type;
// 	char			*file_name;
// 	struct s_redir	*next;
// }	t_redir;

// typedef struct s_cmd
// {
// 	char			**argv; // because execve expects execve(path, argv, envp);
// 	t_redir			*redir; // redir only setup for the fd, not needed by execve
// 	struct s_cmd	*next;
// }	t_cmd;

// typedef struct s_data
// {
// 	//head of the list 
// 	//t_env	*envp_list;
// 	//bool	exit_flag;
// 	int		exit_code;

// } t_data;

typedef struct s_cmd
{
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;


void execute_cmd(char *name)
{
	char	buffer[100];
	int		n;
	
    write(1, name, strlen(name));
    write(1, "\n", 1);
	n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	
	if (n > 0)
	{
		buffer[n] = '\0';
		printf("%s received: %s\n", name, buffer);
	}
    exit(0);
}

//i should be passing the 
void	traverse_cmd(t_cmd *cmd)
{
	int 		pipefd[2];
	int			prev_cmd_read_end;
	pid_t		pid;
	
	prev_cmd_read_end = STDIN_FILENO;
	while (cmd)
	{
		pipe(pipefd);//for each command, create thier own pipes
		pid = fork();
		if (pid == 0)//if child proceess
		{			
			if (prev_cmd_read_end != 0)
			{
				dup2(prev_cmd_read_end, STDIN_FILENO); //if there is previous pipe, make the stdin of current process the preivious pipe's read end (now stdin of the process is the read end of previous process)
				close (prev_cmd_read_end); //close this fd within the child
			}
			if (cmd->next) //if there is a next cmd, then output the stdout to the write end of the pipe
			{
				dup2(pipefd[1], STDOUT_FILENO); //the stdout will now point to the pipefd[1], so you can delete the pipefd[1](write end)
			}
			close (pipefd[1]); //if there are no cmd->next the output should be done to stdout and close the write end of the pipe
			close (pipefd[0]); //close the unused read end of the pipe 
			execute_cmd(cmd->argv[0]) ;	
		}
		else if (pid > 0)
		{
			close(pipefd[1]); // always close write end in parent
			if (cmd->next)
			{
				dup2(pipefd[0], prev_cmd_read_end); //issue is might accidentally close stdin (0) forever?

				prev_cmd_read_end = pipefd[0]; //issue is should i dup2 or just assign?
				//char x = prev_cmd_read_end + '0';
				//write(1, &x , 1);
				//dup2(pipefd[0], prev_cmd_read_end);
			}
			else
				close(pipefd[0]);
			cmd = cmd->next;
		}
	}
}

int	main(void)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	t_cmd	cmd3;

	char *argv1[] = {"cmd1", NULL};
	char *argv2[] = {"cmd2", NULL};
	char *argv3[] = {"cmd3", NULL};

	cmd1.argv = argv1;
	cmd2.argv = argv2;
	cmd3.argv = argv3;

	cmd1.next = &cmd2;
	cmd2.next = &cmd3;
	cmd3.next = NULL;

	traverse_cmd(&cmd1);

	return (0);
}