/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckin-yew <ckin-yew@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:18:56 by ckin-yew          #+#    #+#             */
/*   Updated: 2026/06/05 19:18:57 by ckin-yew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_redir(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir->file_name);
		if (redir->heredoc_file)
		{
			unlink(redir->heredoc_file);
			free(redir->heredoc_file);
		}
		free(redir);
		redir = next;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free_argv(cmd->argv);
		free_redir(cmd->redir);
		free(cmd);
		cmd = next;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = next;
	}
}
