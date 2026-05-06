#ifndef AST_H
#define AST_H

//basiclaly whats understood is that if the thing will cause the ast to split then it will need a node 

typedef enum e_token_type
{
	COMMAND, // the node
	PIPE, //node
	REDIR_IN,	//< redirects stdin from x
	REDIR_OUT, //> replace
	REDIR_APPEND, //>> append to fule
	REDIR_HEREDOC, //<< heredoc
}	t_token_type;

//in code i need to chekc '<' or '<<' then assign meaing 
//the command will contain redirection and words therefore
typedef struct s_redir //will contain the redirtype and the file , but if there is a follow up redir then its an issue 
{
	t_token_type	redir_type; //store the enum 
	char			*file_name; //but what if there is no file
	struct s_redir	*redir_next; //does this need to be an address?
	//need heredc fd
}	t_redir;


typedef struct s_ast
{
	//need something else here but not sure yet 
	t_token_type	token_type; //either pipe or cmd
	struct t_ast	*left;
	struct t_ast	*right;
	struct t_redir	*redir;
	char			**argv; //under exceve format ("cat", "ahshda") or grep ("grep", "-a", "-o")
}	t_ast;

#endif

//redirections do not execute commands, they merely tell the shell where to output the commands 
// they must be a pointer , it acts as a linked list , or else its already initialized ... 