/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:21:23 by ckin-yew          #+#    #+#             */
/*   Updated: 2026/06/06 06:04:11 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_input(char *line, t_cmd **cmds, t_data *data)
{
	t_token	*tokens;

	tokens = tokenising(line);
	if (!tokens)
	{
		data->exit_code = 2;
		return (0);
	}
	*cmds = parsing(tokens);
	free_tokens(tokens);
	if (!*cmds)
	{
		data->exit_code = 2;
		return (0);
	}
	return (1);
}

int	prepare_cmds(t_cmd *cmds, t_data *data)
{
	if (!process_heredoc_q(cmds))
	{
		data->exit_code = 1;
		ft_putstr_fd("minishell: heredoc quote processing failed\n", 2);
		return (0);
	}
	if (!run_heredoc_with_signal(cmds, data))
		return (0);
	if (!expand_cmds(cmds, data->envp_list, data->exit_code))
	{
		data->exit_code = 1;
		ft_putstr_fd("minishell: expansion error\n", 2);
		return (0);
	}
	return (1);
}

int	execute_line(char *line, t_data *data)
{
	t_cmd	*cmds;

	handle_prompt_signal(data);
	if (check_first(line) == 0)
		return (free(line), 1);
	add_history(line);
	if (!parse_input(line, &cmds, data))
		return (free(line), 1);
	if (!prepare_cmds(cmds, data))
	{
		free_cmd(cmds);
		free(line);
		return (1);
	}
	data->exit_code = traverse_pipe_cmd(cmds, data);
	free_cmd(cmds);
	free(line);
	if (data->exit_flag)
		return (0);
	return (1);
}

int	check_first(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
	//	free (line);
		return (0);
	}
	return (1);
}

int	expand_cmds(t_cmd *cmd, t_env *envp, int last_status)
{
	while (cmd)
	{
		if (!(expand_argv(cmd, envp, last_status)))
			return (0);
		if (!(expand_redir(cmd, envp, last_status)))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
