#include "minishell.h"

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
	while (result && str[i])
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

int	has_quotes(char *str)
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

int	handle_heredof_eof(t_redir *redir, int fd)
{
	if (g_signal == SIGINT)
	{
		close(fd);
		return (0);
	}
	ft_putstr_fd("minishell: warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(redir->file_name, 2);
	ft_putstr_fd("')\n", 2);
	return (1);
}

char	*create_hd_filename(void)
{
	static int	i;
	char		*num;
	char		*file;

	num = ft_itoa(i);
	if (!num)
		return (NULL);
	file = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	if (!file)
		return (NULL);
	i++;
	return (file);
}

int	process_heredoc_line(t_redir *redir, char **line,
	t_env *envp, int last_status)
{
	if (ft_strcmp(*line, redir->file_name) == 0)
	{
		free(*line);
		return (2);
	}
	if (redir->heredoc_quote == 0)
	{
		if (!expand_heredoc_line(line, envp, last_status))
			return (0);
	}
	return (1);
}