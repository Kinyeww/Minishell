#include "minishell.h"

int	open_hd_file(t_redir *redir)
{
	int	fd;

	redir->heredoc_file = create_hd_filename();
	if (!redir->heredoc_file)
		return (-1);
	fd = open(redir->heredoc_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(redir->heredoc_file);
		redir->heredoc_file = NULL;
		return (-1);
	}
	return (fd);
}

char	*expand_heredoc(char *line, t_env *envp, int last_status)
{
	int		i;
	char	*result;
	char	*value;

	i = 0;
	result = ft_strdup("");
	while (result && line[i])
	{
		if (line[i] == '$')
		{
			value = expand_var(line, &i, envp, last_status);
			if (!value)
			{
				free (result);
				return (NULL);
			}
			result = append_str(result, value);
			free(value);
			continue ;
		}
		result = append_char(result, line[i]);
		i++;
	}
	return (result);
}

int	expand_heredoc_line(char **line, t_env *envp, int last_status)
{
	char	*expanded;

	expanded = expand_heredoc(*line, envp, last_status);
	free(*line);
	*line = expanded;
	if (!*line)
		return (0);
	return (1);
}
