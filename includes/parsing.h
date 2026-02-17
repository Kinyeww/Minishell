#ifndef PARSING_H
# define PARSING_H

#include "tokenising.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char 			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*parsing(t_token *tokens);
t_token	*tokenising(char *line);

#endif