#include "../includes/parsing.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_strcmp(const char *s1, const char *s2);
static void	assign_meaning(t_token *tokens);

void	print_meaning(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	printf("printing tokens\n");
	while (tokens)
	{
		if (tokens->type == WORD)
			printf("token[%s] = %d[word]\n", tokens->content, tokens->type);
		else if (tokens->type == PIPE)
			printf("token[%s] = %d[pipe]\n", tokens->content, tokens->type);
		else if (tokens->type == REDIR_IN)
			printf("token[%s] = %d[REDIR_IN]\n", tokens->content, tokens->type);
		else if (tokens->type == REDIR_OUT)
			printf("token[%s] = %d[REDIR_OUT]\n", tokens->content, tokens->type);
		else if (tokens->type == APPEND)
			printf("token[%s] = %d[APPEND]\n", tokens->content, tokens->type);
		else if (tokens->type == HEREDOC)
			printf("token[%s] = %d[HEREDOC]\n", tokens->content, tokens->type);
		tokens = tokens->next;
	}
}

t_token	*parsing(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	printf("--- assigning meaning ---\n");
	while (tokens)
	{
		assign_meaning(tokens);
		tokens = tokens->next;
	}
	tokens = head;
	print_meaning(tokens);
	return (head);
}

/*always check for longer char first*/
static void	assign_meaning(t_token *tokens)
{
	printf("assigning meaning for %s\n", tokens->content);
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

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
