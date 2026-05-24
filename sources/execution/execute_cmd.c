/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:27:29 by syee              #+#    #+#             */
/*   Updated: 2026/05/24 22:23:51 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h> //close(), dup2()
#include <fcntl.h>

typedef enum e_fd_action_type
{
	RESTORE,
	COPY
} t_fd_action_type;

//before traverse cmd or during ?  
void dup_restore_fd(t_fd_action_type type)
{
	static int stdin_copy;
	static int stdout_copy;
	
	if (type == RESTORE)
	{
		dup2(stdin_copy, 0);
		close (stdin_copy); //this make it so that i cant call it multiple times
		dup2(stdout_copy, 1);
		close (stdout_copy); //this make it so that i cant call it multiple times
	}
	else if (type == COPY)
	{
		stdin_copy = dup(0);
		stdout_copy = dup(1);
	}
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

//now heres the big issue , how does returning the errors work here 

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

int built_in_setup_and_execute(t_cmd *cmd, t_data *data)
{
	int	built_in_return_val;

	built_in_return_val = 0;
	if (cmd->redir != NULL) 
	{
		dup_restore_fd(COPY);

		if (setup_redirections(cmd) != 0)
			return (dup_restore_fd (RESTORE), 1);

		built_in_return_val = execute_built_ins(cmd->argv, data);
		dup_restore_fd(RESTORE);
	}
	else 
		built_in_return_val = execute_built_ins(cmd->argv, data);

	//update exit_code using the built_in_return_val ?
	return (0);
}

/*
1. Check if there are redirection
	2a. if there is setup
		2ai. if redirection fails, free every malloced stuff and exit
		
*/

int binary_setup_and_execute(t_cmd *cmd, t_data *data)
{
	int child_pid;
	
	child_pid = fork();

	if (child_pid == 0)
	{
		if (cmd->redir != NULL)
		{
			if (setup_redirections(cmd) != 0) //if redirections fail to setup
			{
				free_data(); //free other exisiting data to prevent leaks
				exit(1);
			}
		}
		if (execute_binary(cmd) > 0) //if there are any returns?
		{
			free_data(); //free other exisiting data to prevent leaks
			exit(1);
		}
	}
	else //this part needs to be researched on the syntax to be coded properly 
	{
		waitpid(child_pid, status, option);
		if (status == error)
		{
			print_err();
			update_exit_code();
		}
	}
}
/*
there is no checking if pipe or if no pipe, if there are subsequent commands then it has a pipe

*/
void traverse_cmd_list (t_cmd *cmd, t_data *data)
{
	while (cmd)
	{
		if (cmd->next != NULL)
			setup_pipes();

		if (check_built_in(cmd->argv[0]) != 0)
			built_in_setup_and_execute(cmd, data);
		else
			binary_setup_and_execute(cmd, data);
		
		cmd = cmd -> next;
	}
}


//the redirections connecting to the current one will overwrite the fd 
int setup_redirections(t_cmd *cmd)
{
	t_redir *redir;
	
	redir = cmd -> redir;
	int file_fd;
	
	while (redir)
	{
		if (redir -> redir_type == REDIR_IN) // cmd < file
		{
			 file_fd = open(redir->file_name, O_RDONLY);
			
			if (file_fd == -1)
				return(err_msg(NO_FILE_EXISTS), update_exit_code(), 1);
			
			dup2(file_fd , STDIN_FILENO); //i dont have to care because if stdin is manipulated, it's file description will be manipulated 
			close (file_fd);
			
		}
		else if (redir ->redir_type == REDIR_OUT) // cmd > file
		{
			 file_fd = open(redir->file_name , O_wRONLY | O_TRUNC | O_CREAT);
			 
			if (file_fd == -1)
				return(err_msg(err), update_exit_code(), 1);

			dup2(file_fd , STDOUT_FILENO); //stdout now points to file fd
			close (file_fd);
		}
		else if (redir -> redir_type == APPEND) // cmd > file
		{
			file_fd = open(redir->file_name , O_wRONLY | O_APPEND | O_CREAT);
			
			if (file_fd == -1)
				return(err_msg(err), update_exit_code(), 1);
			
			dup2(file_fd, STDOUT_FILENO);
			close (file_fd);
		}
	redir = redir -> next;
	}
	return (0);
}


 