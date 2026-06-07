/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:21:16 by syee              #+#    #+#             */
/*   Updated: 2026/06/07 14:31:58 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_restore_fd(t_data *data)
{
	dup2(data->fd_copy[0], STDIN_FILENO);
	dup2(data->fd_copy[1], STDOUT_FILENO);
}
/*
When a command terminates on a fatal signal N, bash uses the value 128+N 
as the exit status.
*/

void	print_err_redir(char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, "\n", 1);
}

int	check_built_in(char *argv1)
{
	if (ft_strcmp("echo", argv1) == 0 || ft_strcmp("cd", argv1) == 0
		|| ft_strcmp("pwd", argv1) == 0 || ft_strcmp("export", argv1) == 0
		||ft_strcmp("unset", argv1) == 0 || ft_strcmp("env", argv1) == 0
		||ft_strcmp("exit", argv1) == 0)
		return (1);
	else
		return (0);
}
