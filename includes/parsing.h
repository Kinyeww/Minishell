#ifndef PARSING_H
# define PARSING_H

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
	char 			*token;
}	t_token;

int	parsing(char *str);
// int	tokenising(char *str, t_token *tokens);

#endif