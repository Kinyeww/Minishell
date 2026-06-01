#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int	check_first(char *line);
static void	print_command(t_cmd *cmd);
static char	*redir_name(t_token_type redir_name);
void		print_heredoc_files(t_cmd *cmds);
void	create_envp_list(t_env **envp_list, char **envp); 


void init_data(t_data *data, char **envp)
{
	data->envp_list = NULL;
	data->exit_flag = false;
	data->exit_code = 0;
	create_stdin_stdout_cpy(data);
	create_envp_list(&data->envp_list, envp);
}

void data_clean(t_data *data)
{
	envp_list_clean(&data->envp_list);
	close (data->fd_copy[0]);
	close (data->fd_copy[1]);
	free(data);
}
//rmbr to close later on?
void	create_stdin_stdout_cpy(t_data *data)
{
	data->fd_copy[0] = dup(STDIN_FILENO);
	data->fd_copy[1] = dup(STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	t_data	data;
	int		exit_code;

	(void) ac;
	(void) av;
	//====syee add====
	init_data(&data, envp);
	exit_code = 0;

	rl_catch_signals = 0;

	while (1)
	{
		set_signal_prompt();
		line = readline("Minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (g_signal == SIGINT)
		{
			data.exit_code = 130;
			g_signal = 0;
		}
		if (check_first(line) == 0)
			continue ;			
		add_history(line);
		tokens = tokenising(line);
		if (!tokens)
		{
			data.exit_code = 2;
			free(line);
			continue ;
		}
		cmds = parsing(tokens);
		free_tokens(tokens);
		if (!cmds)
		{
			data.exit_code = 2;
			free(line);
			continue ;
		}
		if (!process_heredoc_q(cmds))
		{
			data.exit_code = 1;
			ft_putstr_fd("minishell: heredoc quote processing failed\n", 2);
			free_cmd(cmds);
			free(line);
			continue ;
		}
		if (!run_heredoc_with_signal(cmds, &data))
		{
			free_cmd(cmds);
			free(line);
			continue ;
		}
		if (!expand_cmds(cmds, data.envp_list, data.exit_code))
		{
			data.exit_code = 1;
			ft_putstr_fd("minishell: expansion: error\n", 2);
			free_cmd(cmds);
			free(line);
			continue ;
		}

		print_command(cmds); //is this for debugging ?
		print_heredoc_files(cmds);

		//=== syee add , run execution ====
		data.exit_code = traverse_pipe_cmd(cmds, &data);
		
		//=== kinyew frees =====
		free_cmd(cmds);
		free(line);

		//=== syee add , if exit_flag is true quit ====
		if (data.exit_flag)
		{
			exit_code = data.exit_code;
			data_clean (&data);
			break ;
		}
	}

	return (exit_code);
}


/*
jun 1 
- changed data.exit_code to exit code variable in main, due to the need to clean up code before exit
*/

//commented out as merged
// void create_envp_list(t_env **envp_list, char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	*ptr;
// 	t_env	*new;

// 	i = 0;
// 	j = 0;
// 	while (envp[i])
// 	{
// 		new = malloc(sizeof(t_env));
// 		if (!new)
// 			return;
// 		ptr = ft_strchr(envp[i], '=');
// 		j = ptr - envp[i];
// 		new->key = ft_strndup(envp[i], j);
// 		new->value = ft_strdup(ptr + 1);
// 		new->next = NULL;
// 		list_add_back(envp_list, new);
// 		i++;
// 	}
// 	return ;
// }

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
				printf("heredoc content:\n");
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

void data_clean(t_data *data)
{
	envp_list_clean(&data->envp_list);
	free(data);
}