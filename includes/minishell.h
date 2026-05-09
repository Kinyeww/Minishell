#ifndef MINISHELL_H
# define MINISHELL_H

//#include "parsing.h"



/* =============== AST =============== */
typedef enum e_token_type
{
	COMMAND,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
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

/* =============== env =============== */
typedef struct s_env t_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

/* =============== MainStruct =============== */

typedef struct s_data
{
	t_env	*envp_list;
	//t_exit	exit_status;
} t_data;

/* ============ Utils =====================*/
int	ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *str);
char *ft_strdup(char *string);
char *ft_strchr(char *string, char c);
char *ft_strndup(char *string , int size);

#endif
