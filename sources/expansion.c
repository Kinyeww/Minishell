#include "../includes/minishell.h"
#include <stdlib.h>
#include <stdio.h>

static int	error_handling(t_token *tokens);
static void	parse_pipeline(t_token *tokens);
static t_token	*find_pipe(t_token *tokens);

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

t_token	*expand(t_token *tokens, char **envp)
{
	printf("--- expanding ---\n");
	if (error_handling(tokens) != 0)
		return (NULL);
	printf("no error found\n");
	parse_pipeline(tokens); /* check if theres pipe first */
	parse_command(tokens);
	return (tokens);
}

static void	parse_pipeline(t_token *tokens)
{
	t_token	*pipe;
	t_ast	*ast;

	pipe = find_pipe(tokens);
	if (!pipe)
		return (parse_command(tokens));
	ast = create_ast(tokens, pipe);
}

static void	parse_command(t_token **curr_tokens)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	while (*curr_tokens && (*curr_tokens)->type != PIPE)
	{
		if (is_redir(*curr_tokens->type))
		{
			add_redir()
			cur->next;
		}
		else if (==word)
		{
			add_arg
			cur->next
		}
	}
	return (cmd);
}

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == APPEND
		|| type == HEREDOC);
}

static t_cmd	*cmd_init(void)
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

static int	error_handling(t_token *tokens)
{
	if (tokens && tokens->type == PIPE)
	{
		printf("pipe cannot be first\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (tokens->next == NULL || tokens->next->type != WORD)
			{
				printf("redirections must followed by a word\n");
				return (1);
			}
		}
		else if (tokens->type == PIPE)
		{
			if (tokens->next && tokens->next->type == PIPE)
			{
				printf("no double pipes, we're not doing tat sorry :)\n");
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static t_token	*find_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}