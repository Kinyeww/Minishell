#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void		assign_meaning(t_token *tokens);
static int		error_handling(t_token *tokens);
static t_cmd	*parse_pipeline(t_token **tokens);
static t_cmd	*parse_command(t_token **curr_tk);

static int	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

t_cmd	*parsing(t_token *tokens)
{
	t_token	*head;
	t_cmd	*cmds;

	head = tokens;
	while (tokens)
	{
		assign_meaning(tokens);
		tokens = tokens->next;
	}
	tokens = head;
	if (error_handling(head) == 1)
		return (NULL);
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

static int	error_handling(t_token *tokens)
{
	if (tokens && tokens->type == PIPE)
		return (print_syntax_error("|"));
	while (tokens)
	{
		if (tokens->type == REDIR_IN || tokens->type == REDIR_OUT
			|| tokens->type == APPEND || tokens->type == HEREDOC)
		{
			if (tokens->next == NULL)
				return (print_syntax_error("newline"));
			if (tokens->next->type != WORD)
				return (print_syntax_error(tokens->next->content));
		}
		else if (tokens->type == PIPE)
		{
			if (tokens->next == NULL)
				return (print_syntax_error("newline"));
			if (tokens->next->type == PIPE)
				return (print_syntax_error("|"));
		}
		tokens = tokens->next;
	}
	return (0);
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
