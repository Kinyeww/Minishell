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
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	t_token_type	redir_type;
	char			*file_name;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv; // because execve expects execve(path, argv, envp);
	t_redir			*redir; // redir only setup for the fd, not needed by execve
	struct s_cmd	*next;
}	t_cmd;

/*tokenising*/
t_token	*tokenising(char *line);

/*parsing*/
t_cmd	*parsing(t_token *tokens);

/*parsing_utils*/
int		ft_strcmp(const char *s1, const char *s2);
t_cmd	*cmd_init(void);
int		is_redir(t_token_type type);
char	*ft_strdup(char *src);

/*parsing_r&c*/
int		add_redir(t_cmd	*cmd_list, t_token_type r_type, char *file_name);
int		add_arg(t_cmd *cmd_list, char *content);

#endif