#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>

int			prepare_heredoc(t_cmd *cmds, t_env *envp, int last_status);
int			read_heredoc(t_redir *redir, t_env *envp, int last_status);
int			process_heredoc_q(t_cmd *cmds);
static char	*create_hd_filename(void);
static int	open_hd_file(t_redir *redir);
char		*expand_heredoc(char *line, t_env *envp, int last_status);


char	*ft_combine(size_t len1, size_t len2, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*temp;

	temp = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		temp[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len2)
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[len1 + len2] = '\0';
	return (temp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = 0;
	while (s1[len1] != '\0')
		len1++;
	len2 = 0;
	while (s2[len2] != '\0')
		len2++;
	str = ft_combine(len1, len2, s1, s2);
	return (str);
}

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

int	read_heredoc(t_redir *redir, t_env *envp, int last_status)
{
	char	*line;
	char	*expanded;
	int		fd;

	fd = open_hd_file(redir);
	if (fd == -1)
		return (0);
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
			expanded = expand_heredoc(line, envp, last_status);
			free(line);
			line = expanded;
			if (!line)
			{
				close (fd);
				return (0);
			}
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (1);
}

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

static char	*create_hd_filename(void)
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

static int	open_hd_file(t_redir *redir)
{
	int	fd;

	redir->heredoc_file = create_hd_filename();
	if (!redir->heredoc_file)
		return (-1);
	fd = open(redir->heredoc_file, O_CREAT | O_WRONLY | O_TRUNC , 0600);
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
	if (!result)
		return (NULL);
	while (line[i])
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
			if (!result)
				return (NULL);
			continue ;
		}
		else
		{
			result = append_char(result, line[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
