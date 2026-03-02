#include "../includes/minishell.h"
#include <stdio.h>
/*
to-do
1. validate (make sense)
2. create a grammar rule and follow (error handling)
3. can start doing the expansion, but we need to decide how to do it first
*/
static int	error_handling(t_token *tokens);

t_token	*expand(t_token *tokens, char **envp)
{
	printf("--- expanding ---\n");
	if (error_handling(tokens) != 0)
		return (NULL);
	return (tokens);
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
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT)
		{
			if (tokens->next == NULL || tokens->next->type != WORD)
			{
				printf("redirections must followed by a word\n");
				return (1);
			}
		}
		else if (tokens->type == PIPE)
		{
			if (tokens->next->type == PIPE)
			{
				printf("no double pipes, we're not doing tat sorry :)\n");
				return (1);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
