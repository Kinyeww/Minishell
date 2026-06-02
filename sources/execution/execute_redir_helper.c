/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 21:21:16 by syee              #+#    #+#             */
/*   Updated: 2026/06/02 21:23:13 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_restore_fd(t_data *data)
{
	dup2(data->fd_copy[0], STDIN_FILENO);
	dup2(data->fd_copy[1], STDOUT_FILENO);
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