#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "expansion.h"

typedef struct s_data
{
	t_env	*envp_list;
	bool	exit_flag;
	int		exit_code;
}	t_data;

void create_envp_list(t_env **envp_list, char **envp);
int	process_heredoc_q(t_cmd *cmds);
int	prepare_heredoc(t_cmd *cmds, t_env *envp, int last_status);

#endif