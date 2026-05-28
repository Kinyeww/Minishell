#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	check_first(char *line);
static void	print_command(t_cmd *cmd);
static char	*redir_name(t_token_type redir_name);
void print_env_list(t_env *list);
void	print_heredoc_files(t_cmd *cmds);

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	t_data	data;

	(void) ac;
	(void) av;
	data.envp_list = NULL;
	create_envp_list(&envp_list, envp);
	print_env_list(envp_list);
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (check_first(line) == 0)
			continue ;			
		add_history(line);
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
		if (!process_heredoc_q(cmds))
		{
			printf("heredoc quote processing failed\n");
			free_cmd(cmds);
			free(line);
			continue ;
		}
		if (!expand_cmds(cmds, envp_list, 0))
		{
			printf("expansion failed\n");
			free_cmd(cmds);
			free(line);
			continue ;
		}
		if (!prepare_heredoc(cmds, envp_list, 0))
		{
			printf("heredoc preparation failed\n");
			free_cmd(cmds);
			free(line);
			continue ;
		}
		print_command(cmds);
		print_heredoc_files(cmds);
		free_cmd(cmds);
		free(line);
	}
	return (0);
}

void print_env_list(t_env *list)
{
    while (list)
    {
        printf("%s=%s\n", list->key, list->value);
        list = list->next;
    }
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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	print_heredoc_files(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		fd;
	char	buf[1025];
	int		bytes;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->redir_type == HEREDOC)
			{
				printf("\n--- HEREDOC DEBUG ---\n");
				printf("delimiter = %s\n", redir->file_name);
				printf("quoted = %d\n", redir->heredoc_quote);
				printf("temp file = %s\n", redir->heredoc_file);
				fd = open(redir->heredoc_file, O_RDONLY);
				if (fd == -1)
				{
					perror("open heredoc debug");
					return ;
				}
				bytes = read(fd, buf, 1024);
				while (bytes > 0)
				{
					buf[bytes] = '\0';
					printf("%s", buf);
					bytes = read(fd, buf, 1024);
				}
				close(fd);
				printf("\n--- END HEREDOC DEBUG ---\n");
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
