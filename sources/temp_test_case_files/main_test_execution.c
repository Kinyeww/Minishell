/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:21:47 by syee              #+#    #+#             */
/*   Updated: 2026/05/29 17:01:29 by syee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test_cases.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

void create_envp_list(t_env **envp_list, char **envp);

void data_clean(t_data *data);
void cleanup_cmd(t_cmd *cmd);
void cleanup_cmds(t_cmd *cmd);

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	//printf("starting in main \n");

	t_data	*data;
	t_cmd	*test1;
	t_cmd	*test2;
	t_cmd	*test3;
	t_cmd	*test4;
	t_cmd	*test5;

	data = malloc (sizeof(t_data));
	*data = (t_data){0};
	create_envp_list(&data->envp_list, envp);

	test1 = test_case_1();
	/*
	- testing with binary cat
	- testing with unavailable file 
	- 
	*/

	// test2 = test_case_2();
	// test3 = test_case_3();
	// test4 = test_case_4();
	// test5 = test_case_5();

	execute_cmd(test1, data);
	cleanup_cmd(test1);
	
	data_clean(data);

	return (0);
}

void cleanup_cmd(t_cmd *cmd)
{
	int		index;
	t_redir	*redir;
	t_redir	*next_redir;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		index = 0;
		while (cmd->argv[index])
		{
			free(cmd->argv[index]);
			index++;
		}
		free(cmd->argv);
	}

	redir = cmd->redir;
	while (redir)
	{
		next_redir = redir->next;
		free(redir->file_name);
		free(redir);
		redir = next_redir;
	}
	free(cmd);
}

void cleanup_cmds(t_cmd *cmd)
{
	t_cmd *next_cmd;

	while (cmd)
	{
		next_cmd = cmd->next;
		cleanup_cmd(cmd);
		cmd = next_cmd;
	}
}

void data_clean(t_data *data)
{
	envp_list_clean(&data->envp_list);
	free(data);
}
