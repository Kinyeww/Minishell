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
	int				heredoc_quote; // only used for heredoc, for other redir types, this will be -1
	char			*heredoc_file;
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

/*free_parsing*/
void	free_argv(char **argv);
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token *tokens);


#endif