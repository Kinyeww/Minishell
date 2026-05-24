/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 18:27:29 by syee              #+#    #+#             */
/*   Updated: 2026/05/24 20:15:39 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
int built_in_check_execute(t_cmd *cmd)
{
	
	if (cmd->redirections) 
	{
		if (setup_redirections(cmd) == 1)
		{
			dup_restore_fd (RESTORE);
			continue ; //it should restore, in the case that there are multiple connecting redirections, if the earlier ones succeed and the upcoming ones fail, it should be fixed && if continue is placed here then how will the cmd be updated? 
	
		}
			execute builtin();
		dup_restore_fd(RESTORE);
	}
	else 
	{
		execute_builtin();
	}
	return (0);
}
void traverse cmd (t_cmd *cmd)
{
	while (cmd)
	{
		dup_restore_fd(COPY); //reconsider ? does this belong to entire traversal or one built_in execution, based on redir alone w no pipes, 
		if (cmd->cmd_type == commands)
		{
			if (check_builtin(cmd) == true)
			{
				
			}
			else
			{
			   int child_pid = fork() ;
			    if (child_pid == 0)
			    {
				if (cmd->redirections)
				{
					if (setup_redirections(cmd) == 1)
					{
						 return_error();
				 		 free_data();
						  exit(1);
					}
				}
		
			       if (execute binary(cmd)== false)
				{
				  return_error();
				  free_data();
				  exit(1);
				}
			    }
			    else
			    {
				waitpid(child_pid, status, option);
				if (status == error)
				{
					print_err(cmd not found);
					update_exit_code();				
				}
			    }
			}
		}
		else if (cmd -> cmd_type == PIPE)
			pipe_setup(); //to be added
			
  		cmd = cmd-> next;
	}
	
}



// here have to consider if there are multiple redirections (cat < in.txt > out.txt) 
/*
reference to the struct : 

typedef struct s_redir
{
	t_token_type	redir_type;
	char			*file_name;
	struct s_redir	*next;
	int 		file_fd;
}	t_redir;
*/

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


 