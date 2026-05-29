#include "test_cases.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static t_cmd *tc_cmd_init(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

static int tc_add_arg(t_cmd *cmd, char *content)
{
	char **new_argv;
	int av_len;
	int i;

	av_len = 0;
	if (cmd->argv)
		while (cmd->argv[av_len])
			av_len++;
	new_argv = malloc(sizeof(char *) * (av_len + 2));
	i = 0;
	while (i < av_len)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(content); //yeah it should return NULL
	new_argv[i + 1] = NULL;
	//printf("new argv : %s", new_argv[0]);
	free(cmd->argv);
	cmd->argv = new_argv;
	return (1);
}

static int tc_add_redir(t_cmd *cmd, t_token_type r_type, char *file_name)
{
	t_redir *new;
	t_redir *tmp;

	new = malloc(sizeof(t_redir));
	new->redir_type = r_type;
	new->file_name = ft_strdup(file_name);
	new->next = NULL;
	if (!cmd->redir)
	{
		cmd->redir = new;
		return (1);
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

t_cmd *test_case_1(void)
{
	t_cmd *cmd;

	cmd = tc_cmd_init();
	tc_add_arg(cmd, "\0");
	tc_add_redir(cmd, REDIR_IN, "notes.txt");
	return (cmd);
}

t_cmd *test_case_2(void)
{
	t_cmd *cmd;

	cmd = tc_cmd_init();
	tc_add_arg(cmd, "echo");
	tc_add_arg(cmd, "hello");
	tc_add_redir(cmd, REDIR_OUT, "out.txt");
	return (cmd);
}

t_cmd *test_case_3(void)
{
	t_cmd *cmd;

	cmd = tc_cmd_init();
	tc_add_arg(cmd, "ls");
	tc_add_redir(cmd, APPEND, "append.txt");
	return (cmd);
}

t_cmd *test_case_4(void)
{
	t_cmd *cmd;

	cmd = tc_cmd_init();
	tc_add_arg(cmd, "grep");
	tc_add_arg(cmd, "test");
	tc_add_redir(cmd, HEREDOC, "EOF");
	return (cmd);
}

t_cmd *test_case_5(void)
{
	t_cmd *cmd;

	cmd = tc_cmd_init();
	tc_add_arg(cmd, "cat");
	tc_add_arg(cmd, "file.txt");
	tc_add_redir(cmd, REDIR_IN, "input.txt");
	tc_add_redir(cmd, REDIR_OUT, "output.txt");
	return (cmd);
}
