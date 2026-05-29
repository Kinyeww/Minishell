/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:21:47 by syee              #+#    #+#             */
/*   Updated: 2026/05/29 19:57:19 by syee             ###   ########.fr       */
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

	//test1 = test_case_1();
	// cmd < file
	/*
	1. testing with binary "cat" with invalid  file : "minishell: input.txt: No such file or directory" //ok
	2. testing with binary "cat" with valid file : All heap blocks were freed -- no leaks are possible in main but still reachable: 7,605 bytes in 267 blocks in child process //ok
	3. testing with built_in "echo" with valid file :  no leaks //ok
	4. testing with built_in "echo" with invalid file : no leaks , "minishell: input.txt: No such file or directory" //ok
	5. testing with invalid command with valid file :  minishell: aa: No such file or directory (invalid command error)
		expected : aasad: command not found //might need to check binary for this
	6. testing with invalid command with invalid file : minishell: balls.txt: No such file or directory
		expected : bash: heua: No such file or directory (files are checked first)
		
		//if there are no argv, and there are redir then just carry out the reidr setup  by right should skip the execution completely
	7. testing with no command (NULL) with invalid file :  minishell: d.txt: No such file or directory //ok
		expected : bash: note.txt: No such file or directory
	8. testing with no command (NULL) with valid file :    ==311017== All heap blocks were freed -- no leaks are possible //ok
		expected : nothing, exit code 0
	9. testing with "\0" with valid file : minishell: : Permission denied ,  //ok
		expected : Command '' not found, but can be installed with:
	10.testing with "\0" with invalid file :==311732==    still reachable: 7,602 bytes in 267 blocks <- leak in child but //ok
		bash: jdnf: No such file or directory
	*/

	 test2 = test_case_2();
	//cmd > file
	/*
	1. testing with binary "cat" with invalid  file :
	2. testing with binary "cat" with valid file : 
	3. testing with built_in "echo" with valid file :
	4. testing with built_in "echo" with invalid file :
	5. testing with invalid command with valid file : 
	6. testing with invalid command with invalid file :
	7. testing with no command (NULL) with invalid file :
	8. testing with no command (NULL) with valid file :
	9. testing with "\0" with valid file : 
	10.testing with "\0" with invalid file :
	*/

	// test3 = test_case_3();
	// test4 = test_case_4();
	// test5 = test_case_5();

	execute_cmd(test2, data);
	cleanup_cmd(test2);
	
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
