#include "minishell.h"

/*
to-do
1. validate (make sense)
2. create a grammar rule and follow
3. 
*/

t_token	*expand(t_token *tokens, char **envp)
{
	if (error_handling(tokens) != 0)
		return (NULL);
}

static int	error_handling(t_token *tokens)
{
	if (tokens->type == PIPE)
	{
		printf("pipe cannot be first\n");
		return (1);
	}
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT)
		{
			tokens = tokens->next;
			if (tokens == NULL || tokens->type != WORD)
			{
				printf("redirections must followed by a word");
				return (1);
			}
		}
		else if (tokens->type == PIPE)
		{
			tokens = tokens->next;
			if (tokens->type == PIPE)
			{
				printf("no double pipes, we're not doing tat sorry :)\n");
				return (1);
			}
		}
		tokens = tokens->next;
	}
}