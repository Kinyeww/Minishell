#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

/*debug*/
static void		print_meaning(t_token *tokens);

static void		assign_meaning(t_token *tokens);
static int		error_handling(t_token *tokens);
static t_cmd	*parse_pipeline(t_token **tokens);
static t_cmd	*parse_command(t_token **curr_tk);

t_cmd	*parsing(t_token *tokens)
{
	t_token	*head;
	t_cmd	*cmds;

	head = tokens;
	printf("--- assigning meaning ---\n");
	while (tokens)
	{
		assign_meaning(tokens);
		tokens = tokens->next;
	}
	tokens = head;
	if (error_handling(head) == 1)
		return (NULL);
	print_meaning(tokens);
	printf("\n---parsing command---\n");
	cmds = parse_pipeline(&tokens);
	if (!cmds)
		return (NULL);
	return (cmds);
}

static t_cmd	*parse_pipeline(t_token **tokens)
{
	t_cmd	*head;
	t_cmd	*curr;
	t_cmd	*new_cmd;

	head = parse_command(tokens);
	if (!head)
		return (NULL);
	curr = head;
	while ((*tokens) && (*tokens)->type == PIPE)
	{
		(*tokens) = (*tokens)->next;
		new_cmd = parse_command(tokens);
		if (!new_cmd)
			return (NULL);
		curr->next = new_cmd;
		curr = new_cmd;
	}
	return (head);
}

static t_cmd	*parse_command(t_token **curr_tk)
{
	t_cmd	*cmd;

	cmd = cmd_init();
	if (!cmd)
		return (NULL);
	while (*curr_tk && (*curr_tk)->type != PIPE)
	{
		if (is_redir((*curr_tk)->type))
		{
			if ((!(*curr_tk)->next) || ((*curr_tk)->next->type != WORD))
				return (NULL);
			if (!add_redir(cmd, ((*curr_tk)->type), (*curr_tk)->next->content))
				return (NULL);
			*curr_tk = (*curr_tk)->next->next;
		}
		else if ((*curr_tk)->type == WORD)
		{
			if (!(add_arg(cmd, (*curr_tk)->content)))
				return (NULL);
			*curr_tk = (*curr_tk)->next;
		}
		else
			return (NULL);
	}
	return (cmd);
}

/*
1. check if pipe is first
2. check if after redir is word onot
3. also check if theres double pipes
*/

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
			if (tokens->next == NULL)
			{
				printf("pipe cannot be last\n");
				return (1);
			}
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

static void	print_meaning(t_token *tokens)
{
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
