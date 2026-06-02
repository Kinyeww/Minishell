#include "minishell.h"
#include "libft_utils.h"
#include <stdlib.h>

/*
to-do
1. parse tokens to t_redir
2. expand env like $HOME = /home/king
3. make execution without pipe works, then with redir, then with pipes

echo hi > out      // REDIR_OUT: create/truncate file, stdout goes there
echo hi >> out     // APPEND: create/append file, stdout goes there
cat < in           // REDIR_IN: stdin comes from file
cat << EOF         // HEREDOC: stdin comes from temporary heredoc input
*/

char	*append_str(char *result, char *to_add);
char	*append_char(char *result, char c);
int		expand_argv(t_cmd *cmd, t_env *envp ,int last_status);
int		expand_cmds(t_cmd *cmd, t_env *envp, int last_status);
int		expand_redir(t_cmd *cmd, t_env *envp, int last_status);
char	*expand_string(char *str, t_env *envp, int last_status);
char	*expand_var(char *str, int *i, t_env *envp, int last_stat);
char	*get_env_val(char *name, t_env *envp);
int		is_var_char(char c);
int		ft_varlen(char *str);

int	expand_cmds(t_cmd *cmd, t_env *envp, int last_status)
{
	while (cmd)
	{
		if (!(expand_argv(cmd, envp, last_status)))
			return (0);
		if (!(expand_redir(cmd, envp, last_status)))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	expand_argv(t_cmd *cmd, t_env *envp ,int last_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		expanded = expand_string(cmd->argv[i], envp, last_status);
		if (!expanded)
			return (0);
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
	return (1);
}

int	expand_redir(t_cmd *cmd, t_env *envp, int last_status)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->redir_type != HEREDOC)
		{
			expanded = expand_string(redir->file_name, envp, last_status);
			if (!expanded)
				return (0);
			free(redir->file_name);
			redir->file_name = expanded;
		}
		redir = redir->next;
	}
	return (1);
}

char	*expand_string(char *str, t_env *envp, int last_status)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*result;
	char	*value;

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (str[i] == '$' && !in_single)
		{
			value = expand_var(str, &i, envp, last_status);
			if (!value)
			{
				free(result);
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
			result = append_char(result, str[i]);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

char	*expand_var(char *str, int *i, t_env *envp, int last_stat)
{
	int		start;
	int		len;
	char	*name;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(last_stat));
	}
	if (!is_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	len = ft_varlen(&str[start]);
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);
	value = ft_strdup(get_env_val(name, envp));
	free(name);
	*i = start + len;
	return (value);
}
