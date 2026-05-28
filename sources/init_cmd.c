#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>

static t_redir	*new_redir(t_token_type r_type, char *file_name);
static int		argv_len(char **argv);

int	add_redir(t_cmd	*cmd_list, t_token_type r_type, char *file_name)
{
	t_redir	*new;
	t_redir	*tmp;

	printf("adding redir\n");
	new = new_redir(r_type, file_name);
	if (!new)
		return (0);
	if (!cmd_list->redir)
	{
		cmd_list->redir = new;
		return (1);
	}
	tmp = cmd_list->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	add_arg(t_cmd *cmd_list, char *content)
{
	char	**new_argv;
	int		av_len;
	int		i;

	printf("adding arg\n");
	av_len = argv_len(cmd_list->argv);
	new_argv = malloc(sizeof(char *) * (av_len + 2));
	if (!new_argv)
		return (0);
	i = 0;
	while (i < av_len)
	{
		new_argv[i] = cmd_list->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(content);
	if (!new_argv[i])
	{
		free(new_argv);
		return (0);
	}
	new_argv[i + 1] = NULL;
	free(cmd_list->argv);
	cmd_list->argv = new_argv;
	return (1);
}

static t_redir	*new_redir(t_token_type r_type, char *file_name)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->redir_type = r_type;
	new->file_name = ft_strdup(file_name);
	if (!new->file_name)
	{
		free(new);
		return (NULL);
	}
	new->heredoc_quote = 0;
	new->heredoc_file = NULL;
	new->next = NULL;
	return (new);
}

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}
