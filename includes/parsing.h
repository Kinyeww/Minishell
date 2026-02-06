#ifndef PARSING_H
# define PARSING_H

typedef struct s_token
{
	char **token;
}	t_token;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
}	t_token_type;

int	parsing(char *str);
int	tokenising(char *str, t_token *tokens);

#endif