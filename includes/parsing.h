#ifndef PARSING_H
# define PARSING_H

typedef struct s_tokenising
{
	int	one_q;
	int	two_q;
	int	intoken;
	int	i;
}	t_tokenising;

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
	struct t_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**argv; // because execve expects execve(path, argv, envp);
	t_redir			*redir; // redir only setup for the fd, not needed by execve
	struct s_cmd	*next;
}	t_cmd;

t_token	*tokenising(char *line);

t_cmd	*parsing(t_token *tokens);
int		ft_strcmp(const char *s1, const char *s2);
t_cmd	*cmd_init(void);
int	is_redir(t_token_type type);

#endif