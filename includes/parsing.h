#ifndef PARSING_H
# define PARSING_H

typedef struct s_token
{
	char *token;
}	t_token;

int	parsing_check(int ac, char **av, t_token *tokens);

#endif