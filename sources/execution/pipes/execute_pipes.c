/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:05:35 by syee              #+#    #+#             */
/*   Updated: 2026/06/06 06:15:18 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

/*
notes on how dup2, dup and pipe work: 

	dup2(old, new) <- new is now new = old
	dup2(fd, 1); // stdout (1) now goes to file , 1 will point to where fd is 

	pipefd[1] ---> pipe ---> pipefd[0]
   	write                    read
*/

int	traverse_pipe_cmd(t_cmd *cmd, t_data *data)
{
	pid_t		pid;
	int			pipefd[2];
	int			prev_read_end;
	int			last_child_pid;

	prev_read_end = -1;
	last_child_pid = 0;
	set_signal_exec_parent();
	if (cmd->next == NULL)
		return (execute_cmd(cmd, data));
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
			setup_pipe_child(prev_read_end, pipefd, cmd, data);
		else if (pid > 0)
			last_child_pid = setup_pipe_parent(pid, pipefd, &prev_read_end, cmd);
		cmd = cmd->next;
	}
	return (wait_child(last_child_pid));
}

int	setup_pipe_parent(int pid, int pipefd[2], int *prev_read_end, t_cmd *cmd)
{
	int	last_child_pid;

	last_child_pid = 0;
	set_signal_exec_parent();
	close(pipefd[1]);
	if (cmd->next)
	{
		if (*prev_read_end != -1)
			close(*prev_read_end);
		*prev_read_end = pipefd[0];
	}
	else
	{
		close(*prev_read_end);
		close(pipefd[0]);
		last_child_pid = pid;
		return (last_child_pid);
	}
	return (0);
}

void	setup_pipe_child(int prev_read_end, int pipefd[2], t_cmd *cmd,
	t_data *data)
{
	set_signal_exec_child();
	if (prev_read_end != -1)
	{
		dup2(prev_read_end, STDIN_FILENO);
		close (prev_read_end);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	exit(execute_cmd(cmd, data));
}

int	wait_child(int last_child_pid)
{
	int	child_process_status;
	int	last_child_status;
	int	pid;

	last_child_status = 0;
	pid = waitpid(-1, &child_process_status, 0);
	while (pid > 0)
	{
		if (last_child_pid == pid)
			last_child_status = child_process_status;
		pid = waitpid(-1, &child_process_status, 0);
	}
	if (WIFSIGNALED(last_child_status))
		return (128 + WTERMSIG(last_child_status));
	else if (WIFEXITED(last_child_status))
		return (WEXITSTATUS(last_child_status));
	return (1);
}
