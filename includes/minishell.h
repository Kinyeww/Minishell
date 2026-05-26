#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "expansion.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

#endif