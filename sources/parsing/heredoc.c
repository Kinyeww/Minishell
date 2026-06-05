#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>

static void	write_heredoc_line(int fd, char *line);
int			process_heredoc_q(t_cmd *cmds);
int			read_heredoc(t_redir *redir, t_env *envp, int last_status);
int			run_heredoc_with_signal(t_cmd *cmds, t_data *data);

int	prepare_heredoc(t_cmd *cmds, t_env *envp, int last_status)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->redir_type == HEREDOC)
			{
				if (!read_heredoc(redir, envp, last_status))
					return (0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	process_heredoc_q(t_cmd *cmds)
{
	t_cmd	*cmd;
	t_redir	*redir;
	char	*clean;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->redir_type == HEREDOC)
			{
				redir->heredoc_quote = has_quotes(redir->file_name);
				clean = remove_quotes(redir->file_name);
				if (!clean)
					return (0);
				free(redir->file_name);
				redir->file_name = clean;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	read_heredoc(t_redir *redir, t_env *envp, int last_status)
{
	t_heredoc	data;

	data.fd = open_hd_file(redir);
	if (data.fd == -1)
		return (0);
	while (1)
	{
		data.line = readline("> ");
		if (!data.line)
		{
			if (!handle_heredoc_eof(redir, data.fd))
				return (close(data.fd), 0);
			break ;
		}
		data.stat = process_heredoc_line(redir, &data.line, envp, last_status);
		if (data.stat == 0)
			return (close(data.fd), 0);
		if (data.stat == 2)
			break ;
		write_heredoc_line(data.fd, data.line);
		free(data.line);
	}
	close(data.fd);
	return (1);
}

int	run_heredoc_with_signal(t_cmd *cmds, t_data *data)
{
	int	stdin_backup;
	int	ok;
	int	interrupted;

	stdin_backup = dup(STDIN_FILENO);
	if (stdin_backup == -1)
		return (0);
	set_signal_heredoc();
	ok = prepare_heredoc(cmds, data->envp_list, data->exit_code);
	interrupted = (g_signal == SIGINT);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	set_signal_prompt();
	if (interrupted)
	{
		data->exit_code = 130;
		g_signal = 0;
		return (0);
	}
	return (ok);
}

static void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
}
