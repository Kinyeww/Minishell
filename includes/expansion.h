#ifndef EXPANSION_H
# define EXPANSION_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

char	*expand_var(char *str, int *i, t_env *envp, int last_status);
char	*get_env_value(char *name, t_env *envp);
int		is_var_char(char c);
char	*append_char(char *result, char c);
char	*append_str(char *result, char *to_add);
int		expand_cmds(t_cmd *cmd, t_env *envp, int last_status);

char	*ft_itoa(int n);
int		ft_strlen(char *str);


#endif