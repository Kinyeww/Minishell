#ifndef ast_H
# define ast_H

# include "parsing.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef struct s_ast
{
	t_node_type		node_type;
	struct t_ast	*left;
	struct t_ast	*right;	
	struct t_redir	*redir;
	char			**argv;
}	t_ast;

t_token	*expand(t_token *tokens, char **envp);

#endif