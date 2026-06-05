/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_setup_cleanup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:23:49 by syee              #+#    #+#             */
/*   Updated: 2026/06/05 19:21:32 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->envp_list = NULL;
	data->exit_flag = false;
	data->exit_code = 0;
	create_stdin_stdout_cpy(data);
	create_envp_list(&data->envp_list, envp);
}

void	data_clean(t_data *data)
{
	envp_list_clean(&data->envp_list);
	close (data->fd_copy[0]);
	close (data->fd_copy[1]);
}
//rmbr to close later on?

void	create_stdin_stdout_cpy(t_data *data)
{
	data->fd_copy[0] = dup(STDIN_FILENO);
	data->fd_copy[1] = dup(STDOUT_FILENO);
}

void	handle_prompt_signal(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->exit_code = 130;
		g_signal = 0;
	}
}
