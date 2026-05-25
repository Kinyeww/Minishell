#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	check_first(char *line);
static void	print_command(t_cmd *cmd);
static char	*redir_name(t_token_type redir_name);

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void) ac;
	(void) av;
	(void) envp;
	while (1)
	{
		line = readline("Minishell$ ");
		if (check_first(line) == 0)
			continue ;
		tokens = tokenising(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		cmds = parsing(tokens);
		free_tokens(tokens);
		if (!cmds)
		{
			free(line);
			continue ;
		}
		printf("--- before expansion ---\n");
		print_command(cmds);
		if (!(expand_cmds(cmds, envp, 0)))
		{
			printf("expansion failed\n");
			free_cmd(cmds);
			free(line);
			continue ;
		}
		printf("----- after expansion -----\n");
		print_command(cmds);
		free_cmd(cmds);
		free(line);
	}
	return (0);
}

static int	check_first(char *line) //empty line check
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		free (line);
		return (0);
	}
	return (1);
}

static void	print_command(t_cmd *cmd)
{
	int		cmd_i;
	int		arg_i;
	t_redir	*redir;

	cmd_i = 0;
	while (cmd)
	{
		printf("\n---command[%d]\n", cmd_i);
		arg_i = 0;
		if (!cmd->argv)
			printf("argv = NULL\n");
		while (cmd->argv && cmd->argv[arg_i])
		{
			printf("argv[%d] = %s\n", arg_i, cmd->argv[arg_i]);
			arg_i++;
		}
		redir = cmd->redir;
		if (!redir)
			printf("redir = NULL\n");
		while (redir)
		{
			printf("redir_type = %s[%d]\nredir_file = %s\n", redir_name(redir->redir_type),redir->redir_type, redir->file_name);
			redir = redir->next;
		}
		cmd = cmd->next;
		cmd_i++;
	}
}

static char	*redir_name(t_token_type redir_name)
{
	if (redir_name == REDIR_IN)
		return ("REDIR_IN");
	else if (redir_name == REDIR_OUT)
		return ("REDIR_OUT");
	else if (redir_name == APPEND)
		return ("APPEND");
	else if (redir_name == HEREDOC)
		return ("HEREDOC");
	return ("no redir found");
}
