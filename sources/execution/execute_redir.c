/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:44 by syee              #+#    #+#             */
/*   Updated: 2026/05/30 15:58:20 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>


/*
GAY edge case 
> file

*/

/*
1. check if it is a built in
	1a. if it is not , quit
2. check if there are redirection
	2a. if there is setup
		2ai. if redirection fails, restore the fds : 
		explaination : it should restore, in the case that there are multiple connecting redirections, 
		if the earlier ones succeed and the upcoming ones fail, it should be fixed
3. run execute_built_ins();
4. update exit code
5. return 0 on success
*/

//update exit code in execute pipes, because here is where the process exists and talks to parent process
int execute_cmd(t_cmd *cmd, t_data *data)
{
	int	return_val;
	
	return_val = 0;
	//if !argv and cmd == TRUE , 
	if ((cmd->argv == NULL || cmd->argv[0] == NULL) && cmd->redir)
	{
		if (setup_redirections(cmd) != 0) //if it fails , redirections are setup first before execution
			return (dup_restore_fd (data), 1);
		return (0);
	}
	if (check_built_in(cmd->argv[0]) != 0)
		return_val = built_in_redir_setup(cmd, data);
	else
		return_val = binary_setup_and_execute(cmd, data);
		
	return(return_val);
}

int check_built_in(char *argv1)
{
	if (ft_strcmp("echo", argv1) == 0 || ft_strcmp("cd", argv1) == 0 ||
		ft_strcmp("pwd", argv1) == 0 || ft_strcmp("export", argv1) == 0 ||
			ft_strcmp("unset", argv1) == 0 || ft_strcmp("env", argv1) == 0 ||
				ft_strcmp("exit", argv1) == 0)
		return (1);
	else
		return (0);
}

void dup_restore_fd(t_data *data)
{
	dup2(data->fd_copy[0], STDIN_FILENO);
	dup2(data->fd_copy[1], STDOUT_FILENO);
}

/*
- for binary, setup the redirections within the binary in the child
- so the fds do not need to be restored
- but if it fails, 
*/

int built_in_redir_setup(t_cmd *cmd, t_data *data)
{
	int	built_in_return_val;

	built_in_return_val = 0;
	if (cmd->redir) 
	{
		if (setup_redirections(cmd) != 0) //if it fails , redirections are setup first before execution
			return (dup_restore_fd (data), 1); //restore the STDIN_FILENO and STDOUT_FILENO
		built_in_return_val = execute_built_ins(cmd->argv, data); //run in execute_built_ins.c
		dup_restore_fd(data);
	}
	else 
		built_in_return_val = execute_built_ins(cmd->argv, data);

	return (built_in_return_val); //update exit_code using the built_in_return_val ?
}

//if its only one process, then.... i think can just run as is as well
int binary_setup_and_execute(t_cmd *cmd, t_data *data)
{
	pid_t 	child_pid;
	pid_t	returned_child_pid;
	int		child_status;
	
	
	child_pid = fork(); //its forked here already so its fine to use exit 
	if (child_pid == 0)
	{
		if (cmd->redir)
		{
			if (setup_redirections(cmd) != 0) //if redirections fail to setup
			{
				//can't just be exit, because it is either within a child process
				//or either within the parent process
				exit (1); //if i return, to the parent
			}
		}
		exit(execute_binary(cmd->argv, data)); //everything from here onwards is a fork
	}
	waitpid (child_pid, &child_status, 0); 
	if (WIFSIGNALED(child_status)) //if the child exited via termination
		return (128 + WTERMSIG(child_status));
	else if (WIFEXITED(child_status))  //if the child exited normally
		return (WEXITSTATUS(child_status));
	else
		return (1);

}

//When a command terminates on a fatal signal N, bash uses the value 128+N as the exit status.

void	print_err_redir(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2); //will show be no such file name or directory
	write(2, "\n", 1);
}
//the redirections connecting to the current one will overwrite the fd 
int setup_redirections(t_cmd *cmd)
{
	int file_fd;
	t_redir *current;

	current = cmd->redir;
	while (current)
	{
		if (current->redir_type == REDIR_IN) //cmd < file
		{
			file_fd = open(current->file_name, O_RDONLY); //O
			if (file_fd == -1)
				return (print_err_redir(current->file_name), 1);
			dup2(file_fd , STDIN_FILENO); //i dont have to care because if stdin is manipulated, it's file description will be manipulated | the stdout will now point to the file_fd
			close (file_fd);
		}
		else if (current->redir_type == REDIR_OUT) // cmd > file
		{
			file_fd = open(current->file_name , O_WRONLY | O_TRUNC | O_CREAT, 0644); //do i need permission or is chatgpt hallucinating 
			if (file_fd == -1)
				return (print_err_redir(current->file_name), 1);
			dup2(file_fd , STDOUT_FILENO); //stdout now points to file fd
			close (file_fd);
		}
		else if (current->redir_type == APPEND) // cmd >> file
		{
			file_fd = open(current->file_name , O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (file_fd == -1)
				return (print_err_redir(current->file_name), 1);
			dup2(file_fd, STDOUT_FILENO);
			close (file_fd);
		}
		current = current->next;
	}
	return (0);
}
