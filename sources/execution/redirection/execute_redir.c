/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 17:08:44 by syee              #+#    #+#             */
/*   Updated: 2026/06/05 18:45:43 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

/*
1. check if it is a built in
	1a. if it is not , quit
2. check if there are redirection
	2a. if there is setup
		2ai. if redirection fails, restore the fds : 
		explaination : it should restore, in the case that
			there are multiple connecting redirections, 
		if the earlier ones succeed and the upcoming ones fail, 
			it should be fixed
3. run execute_built_ins();
4. update exit code
5. return 0 on success
*/
/*
update exit code in execute pipes, because here is where the process exists 
and talks to parent process
*/

int	execute_cmd(t_cmd *cmd, t_data *data)
{
	int	return_val;
	int	i;

	return_val = 0;
	i = 0;
	if ((cmd->argv == NULL || cmd->argv[i] == NULL) && cmd->redir)
	{
		if (setup_redirections(cmd) != 0)
			return (dup_restore_fd (data), 1);
		return (0);
	}
	if (ft_strcmp(cmd->argv[i], "\0") == 0 && (cmd->argv[i + 1] == NULL))
		return (0);
	while (ft_strcmp(cmd->argv[i], "\0") == 0)
		i++;
	if (check_built_in(cmd->argv[i]) != 0)
		return_val = built_in_redir_setup(cmd, data, i);
	else
		return_val = binary_setup_and_execute(cmd, data);
	return (return_val);
}

/*
- for binary, setup the redirections within the binary in the child
- so the fds do not need to be restored
- but if it fails, 
*/
int	built_in_redir_setup(t_cmd *cmd, t_data *data, int i)
{
	int	built_in_return_val;

	built_in_return_val = 0;
	if (cmd->redir)
	{
		if (setup_redirections(cmd) != 0)
			return (dup_restore_fd (data), 1);
		built_in_return_val = execute_built_ins((cmd->argv) + i, data);
		dup_restore_fd(data);
	}
	else
		built_in_return_val = execute_built_ins((cmd->argv) + i, data);
	return (built_in_return_val);
}

int	binary_setup_and_execute(t_cmd *cmd, t_data *data)
{
	pid_t	child_pid;
	pid_t	returned_child_pid;
	int		child_status;

	child_pid = fork();
	if (child_pid == 0)
	{
		set_signal_exec_child();
		if (cmd->redir)
		{
			if (setup_redirections(cmd) != 0)
				exit(1);
		}
		exit(execute_binary(cmd->argv, data));
	}
	set_signal_exec_parent();
	waitpid (child_pid, &child_status, 0);
	if (WIFSIGNALED(child_status))
		return (write(1, "\n", 1), 128 + WTERMSIG(child_status));
	else if (WIFEXITED(child_status))
		return (WEXITSTATUS(child_status));
	else
		return (1);
}
