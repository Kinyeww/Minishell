#include "minishell.h"
#include <stdlib.h>

char	*remove_quotes(char *str)
{
	int		i;
	int		single_q;
	int		double_q;
	char	*result;

	i = 0;
	single_q = 0;
	double_q = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else
		{
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

static int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
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

int	read_heredoc(t_redir *redir, char **envp, int last_status)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file_name) == 0)
		{
			free(line);
			break ;
		}
		if (redir->heredoc_quote == 0)
		{
			expanded = expand_heredoc_line(line, envp, last_status);
			free(line);
			line = expanded;
		}
		//write line into pipe/temp file
		free(line);
	}
	return (1);
}

int	prepare_heredoc(t_cmd *cmds, char **envp, int last_status)
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
