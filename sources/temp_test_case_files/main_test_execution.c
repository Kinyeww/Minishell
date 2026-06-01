/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syee <syee@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 15:21:47 by syee              #+#    #+#             */
/*   Updated: 2026/05/31 19:58:09 by syee             ###   ########.fr       */
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
t_cmd *test_case_pipe_1(void);
t_cmd *test_case_pipe_2(void);
t_cmd *test_case_pipe_3(void);
t_cmd *test_case_exit(void); 
void print_shit(t_cmd *cmd);


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

	// = test_case_1();
	//execute_cmd(test1, data);
	//cleanup_cmd(test1);
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

	//test2 = test_case_2();
	//cmd > file
	//echo hello > file
	/*
	1. testing with binary "ls" with argument & uncreted  file :ls: cannot access 'obama': No such file or directory , no leaks //ok
	2. testing with binary "ls"  & uncreted file : All heap blocks were freed -- no leaks are possible //ok
	3. testing with binary "echo" with word  & uncreated file : ==350893== All heap blocks were freed -- no leaks are possible ok
	4. testing with binary "echo" with word & created file : =351149==   total heap usage: 269 allocs, 269 frees, 7,652 bytes allocated 
	5. testing with invalid command with created file : minishell: die: No such file or directory //ok , leak in child , file gets recreated //ok
	6. testing with invalid command with uncretaed file : same as above and file gets created
	7. testing with no command (NULL) with uncreated file : no leaks at all, all g
			exit code : shd b 0
	8. testing with no command (NULL) with created file : //ok
	10.testing with "\0" with created file : minishell: : No such file or directory //ok
	
	*/

	//test3 = test_case_3();
	// ls >> file
	/*
	- all ok
	*/
	
	// test4 = test_case_4(); //for heredoc can skip
	
	 //test5 = test_case_5(); //double redir
	// cat file.txt < input.txt > output.txt :
	/*
	1. test with uncreated file input : file not found ok
	2. test with valid binary & files, : ok no leaks 
	*/ 

	//cmd3 & cmd1 ok
	//execute_cmd(test3, data);
	//cleanup_cmd(test3);
	
	
	// testing with pipe function 
	
	//t_cmd *pipe_2 = test_case_pipe_2();
	//t_cmd *pipe_3 = test_case_pipe_3();
	//traverse_pipe_cmd returns a value to be updated in the exit code
	
	t_cmd *testexit = test_case_exit();
	int exit_code = traverse_pipe_cmd(testexit , data);
	//update_exit_code(exit_code);
	//printf("exit code : %d\n", exit_code); //this can ensure if the stdout is restored i supposed
	cleanup_cmd(testexit);
	data_clean(data); //clean_envp //exit code cannot be placed in the struct

	return (exit_code); //oh my gosh so thats why they return 0
}
void print_shit(t_cmd *cmd)
{
	t_cmd *current;

	current = cmd;
	while(current)
	{
		int i = 0;
		while (current->argv[i] != NULL)
		{
			printf("%s ",current->argv[i]);
			i++;
		}
		if (current->redir)
		{
			printf("%s", current->redir->file_name);
		}
		
		current = current->next;
		if (current)
			printf("| ");
	}
	printf("\n");
}
	
void cleanup_cmd(t_cmd *cmd)
{
    int     index;
    t_redir *redir;
    t_redir *next_redir;
    t_cmd   *next_cmd;

    while (cmd)
    {
        next_cmd = cmd->next;
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
        cmd = next_cmd;
    }
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
	//close dup_fd
	free(data);
}

