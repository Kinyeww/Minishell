/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:34:53 by syee              #+#    #+#             */
/*   Updated: 2026/06/05 18:43:52 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//the redirections connecting to the current one will overwrite the fd 
int	setup_redirections(t_cmd *cmd)
{
	int		redir_return_value;
	t_redir	*current;

	current = cmd->redir;
	redir_return_value = 0;
	while (current)
	{
		if (current->redir_type == REDIR_IN)
			redir_return_value = setup_redir_in(current->file_name);
		else if (current->redir_type == REDIR_OUT)
			redir_return_value = setup_redir_out(current->file_name);
		else if (current->redir_type == APPEND)
			redir_return_value = setup_redir_append(current->file_name);
		else if (current->redir_type == HEREDOC)
			redir_return_value = setup_redir_heredoc(current->heredoc_file);
		if (redir_return_value == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	setup_redir_in(char *file_name)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1)
		return (print_err_redir(file_name), 1);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
	return (0);
}

int	setup_redir_out(char *file_name)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file_fd == -1)
		return (print_err_redir(file_name), 1);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
	return (0);
}

int	setup_redir_append(char *file_name)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file_fd == -1)
		return (print_err_redir(file_name), 1);
	dup2(file_fd, STDOUT_FILENO);
	close(file_fd);
}

int	setup_redit_heredoc(char *heredoc_file)
{
	int	file_fd;

	file_fd = 0;
	file_fd = open(heredoc_file, O_RDONLY);
	if (file_fd == -1)
		return (perror(heredoc_file), 1);
	dup2(file_fd, STDIN_FILENO);
	close(file_fd);
}
