#include "parsing.h"
#include <stdlib.h>

t_cmd	*cmd_init(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof (t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == APPEND
		|| type == HEREDOC);
}

static void	assign_meaning(t_token *tokens)
{
	if (ft_strcmp(tokens->content, ">>") == 0)
		tokens->type = APPEND;
	else if (ft_strcmp(tokens->content, "<<") == 0)
		tokens->type = HEREDOC;
	else if (ft_strcmp(tokens->content, ">") == 0)
		tokens->type = REDIR_OUT;
	else if (ft_strcmp(tokens->content, "<") == 0)
		tokens->type = REDIR_IN;
	else if (ft_strcmp(tokens->content, "|") == 0)
		tokens->type = PIPE;
	else
		tokens->type = WORD;
}
